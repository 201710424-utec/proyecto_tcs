#ifndef PROYECTO_TCS_HOPCROFT_H
#define PROYECTO_TCS_HOPCROFT_H

#include "../models/Af.h"
#include "../helpers/TransitionHelper.h"
#include <vector>
#include <map>

class Hopcroft {
private:
    Af unminimizedAutomata;
public:
    Hopcroft(Af unminimizedAutomata) {
      this->unminimizedAutomata = unminimizedAutomata;
    };

    Af execute() {
      TransitionHelper delta(unminimizedAutomata);
      std::vector <std::vector <State*>> definedPartition;
      std::vector <std::vector <State*>> undefinedPartition;
      std::vector <State*> currentSet, xSet, ySet;
      std::vector<std::string> alphabet = this->unminimizedAutomata.getAlphabet();
      for (auto stateIt = unminimizedAutomata.get_States().begin(); stateIt != unminimizedAutomata.get_States().end(); stateIt++) {
        if (!unminimizedAutomata.isTerminateState(stateIt->second)) {
          currentSet.push_back(stateIt->second);
        }
      }
      definedPartition.push_back(currentSet);
      currentSet.clear();
      definedPartition.push_back(unminimizedAutomata.get_terminateStates());
      undefinedPartition.push_back(unminimizedAutomata.get_terminateStates());
      while (!undefinedPartition.empty()) {
        xSet.clear();
        currentSet = undefinedPartition.back();
        undefinedPartition.pop_back();
        for (std::vector<std::string>::iterator alphabetIt = alphabet.begin(); alphabetIt != alphabet.end(); alphabetIt++) {
          for (auto stateIt = unminimizedAutomata.get_States().begin(); stateIt != unminimizedAutomata.get_States().end(); stateIt++) {
            if (isInSet(currentSet, unminimizedAutomata.getState(delta.getFirst(stateIt->first, *alphabetIt)))) {
              xSet.push_back(stateIt->second);
            }
          }
          while (true) {
            auto yToRemove = definedPartition.end();
            for (auto definedPartitionIt = definedPartition.begin(); definedPartitionIt != definedPartition.end(); definedPartitionIt++) {
              ySet = *definedPartitionIt;
              if (!setsIntersection(xSet, ySet).empty() && !setsDiference(ySet, xSet).empty()) {
                yToRemove = definedPartitionIt;
                break;
              }
            }
            if (yToRemove == definedPartition.end()) {
              break;
            }else{
              definedPartition.erase(yToRemove);
              definedPartition.push_back(setsIntersection(xSet, ySet));
              definedPartition.push_back(setsDiference(ySet, xSet));
              if (posInPartition(undefinedPartition, ySet) != undefinedPartition.end()) {
                undefinedPartition.erase(posInPartition(undefinedPartition, ySet));
                undefinedPartition.push_back(setsIntersection(xSet, ySet));
                undefinedPartition.push_back(setsDiference(ySet, xSet));
              }else{
                if (setsIntersection(xSet, ySet).size() <= setsDiference(ySet, xSet).size()) {
                  undefinedPartition.push_back(setsIntersection(xSet, ySet));
                }else{
                  undefinedPartition.push_back(setsDiference(ySet, xSet));
                }
              }
            }
          }
        }
      }

      //Create new automata
      Af minimizedAutomata;
      minimizedAutomata.setNumberStates(definedPartition.size());
      std::map<std::vector<State*>, std::string> setStateDix;
      {
      int i = 0;
      for (auto definedPartitionIt = definedPartition.begin(); definedPartitionIt != definedPartition.end(); definedPartitionIt++) {
        setStateDix[*definedPartitionIt] = std::to_string(i);
        minimizedAutomata.addState(std::to_string(i));
        setToState(minimizedAutomata, *definedPartitionIt, unminimizedAutomata, std::to_string(i));
        i++;
      }
      }
      minimizedAutomata.setAllAlphabet(unminimizedAutomata.getAlphabet());
      for (auto itSetStateDix = setStateDix.begin(); itSetStateDix != setStateDix.end(); itSetStateDix++) {
        for (std::vector<std::string>::iterator alphabetIt = alphabet.begin(); alphabetIt != alphabet.end(); alphabetIt++) {
          State* arrivalState = unminimizedAutomata.getState(delta.getFirst(itSetStateDix->first[0]->getTag(), *alphabetIt));
          for (auto itYSetStateDix = setStateDix.begin(); itYSetStateDix != setStateDix.end(); itYSetStateDix++) {
            if (isInSet(itYSetStateDix->first, arrivalState)) {
              minimizedAutomata.addTransition(itSetStateDix->second, *alphabetIt, itYSetStateDix->second);
              break;
            }
          }
        }
      }
      return minimizedAutomata;
    }

    void setToState(Af &minimizedAutomata, std::vector <State*> set, Af unminimizedAutomata, std::string newState) {
      bool terminateState = true;
      bool initialState = false;
      for (auto setIt = set.begin(); setIt != set.end(); setIt++) {
        if (unminimizedAutomata.isInitialState(*setIt)) {
          initialState = true;
        }
        if (!unminimizedAutomata.isTerminateState(*setIt)) {
          terminateState = false;
        }
      }
      if (initialState) {
        minimizedAutomata.addInitialState(newState);
      }
      if (terminateState) {
        minimizedAutomata.addTerminateState(newState);
      }
    }

    bool isInSet (std::vector <State*> set, State* state) {
      for (auto setIt = set.begin(); setIt != set.end(); setIt++) {
        if (*setIt == state) {
          return true;
        } else continue;
      }
      return false;
    }

    std::vector <std::vector <State*>>::iterator posInPartition (std::vector <std::vector <State*>> &partition, std::vector <State*> set) {
      auto pos = partition.end();
      for (auto partitionIt = partition.begin(); partitionIt != partition.end(); partitionIt++) {
        if (*partitionIt == set) {
          pos = partitionIt;
          return pos;
        } else continue;
      }
      return pos;
    }

    std::vector <State*> setsIntersection (std::vector <State*> setA, std::vector <State*> setB) {
      std::vector <State*> intersection;
      for (auto setAIt = setA.begin(); setAIt != setA.end(); setAIt++) {
        for (auto setBIt = setB.begin(); setBIt != setB.end(); setBIt++) {
          if (*setAIt == *setBIt) {
            intersection.push_back(*setAIt);
            break;
          }
        }
      }
      return intersection;
    }

    std::vector <State*> setsDiference (std::vector <State*> setA, std::vector <State*> setB) {
      std::vector <State*> diference;
      for (auto setAIt = setA.begin(); setAIt != setA.end(); setAIt++) {
        diference.push_back(*setAIt);
        for (auto setBIt = setB.begin(); setBIt != setB.end(); setBIt++) {
          if (*setAIt == *setBIt) {
            diference.pop_back();
            break;
          }
        }
      }
      return diference;
    }
};


#endif
