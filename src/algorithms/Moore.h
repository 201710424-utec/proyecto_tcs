#ifndef MOORE
#define MOORE

#import <iostream>
#import <vector>
#import <map>
#import <set>
#import <algorithm>
#import "../helpers/MatrixEquivalencesPixel.h"
#import "../models/Af.h"

template<class T>
class Moore {
 private:
  Af automata;
  std::vector<std::vector<MatrixEquivalencesPixel>> matrix;

  std::vector<T> states;

  // new code
  std::map<int, bool> wasAdded;
  std::set<std::set<int>> sets;

 public:
  Moore(Af automata, std::vector<std::vector<MatrixEquivalencesPixel>> m) {
    this->automata = automata;
    this->matrix = m;
  }

  void exec() {
    this->createStates();
    this->generateSets();
    this->generateAutomata();
  }

  void createStates() {
    for (int i = 0; i < this->automata.getNumberStates(); i++) {
      this->states.push_back(i);
      this->wasAdded[i] = false;
    }
  }

  void generateSets() {
    auto it = this->matrix.begin();
    auto x = 0;
    int i = 0;
    int z = 0;

    // Lower matrix
    for (it++; it != this->matrix.end(); ++it) {
      x++;
      i++;
      z = 0;
      for (auto j = (*it).begin(); j != std::next((*it).begin(), x); j++) {
        // posición exacta
        if (this->matrix[i][z].getValue()) {
          if (!this->wasAdded[i] && !this->wasAdded[z]) {
            std::set<int> temp;
            temp.insert(i);
            temp.insert(z);
            this->sets.insert(temp);
            this->wasAdded[i] = true;
            this->wasAdded[z] = true;
            continue;
          }

          if (!this->wasAdded[i]) {
            this->addToAnExistSet(i, z);
          }

          if (!this->wasAdded[z]) {
            this->addToAnExistSet(z, i);
          }

          this->wasAdded[i] = true;
          this->wasAdded[z] = true;
        }

        z++;
      }
    }

    // Complete set with unary-sets
    for (auto added : this->wasAdded) {
      if (!added.second) {
        std::set<int> temp;
        temp.insert(added.first);
        this->sets.insert(temp);
      }
    }
  }

  // Helper
  void addToAnExistSet(int x, int y) {
    for (auto set : this->sets) {
      for (auto value : set) {
        if (value == y) {
          // Eliminamos y agregamos porque el set o es constante o hace una copia, no se puede pasar referencia.
          std::set<int> temp;
          temp = set;
          temp.insert(x);
          this->sets.erase(set);
          this->sets.insert(temp);
          return;
        }
      }
    }
  }

  void generateAutomata() {
    // Build new automata
    Af newAutomata;
    newAutomata.setAllAlphabet(this->automata.getAlphabet());
    newAutomata.setNumberStates(int(this->sets.size()));

    // map helper to map states.
    std::map<int, std::set<int>> mapHelper;

    // Set all states
    int i = 0;
    for (auto set : this->sets) {
      mapHelper[i] = set;
      newAutomata.addState(std::to_string(i));
      i++;
    }

    // Set initial states
    this->setInitialStates(mapHelper, newAutomata);

    // Set terminate states
    this->setTerminateStates(mapHelper, newAutomata);

    // Set transitions
    this->setTransitions(mapHelper, newAutomata);

    //newAutomata.describe();
    this->automata = newAutomata;
  }

  void describe() {
    this->automata.describe();
  }

  void setInitialStates(std::map<int, std::set<int>> &mapHelper, Af &newAutomata) {
    for (auto initialState : this->automata.get_initialStates()) {
      for (auto state : mapHelper) {
        for (auto value : state.second) {
          if (std::stoi(initialState->getTag()) == value) {
            newAutomata.setInitialState(std::to_string(state.first));
            return;
          }
        }
      }
    }
  }

  void setTerminateStates(std::map<int, std::set<int>> &mapHelper, Af &newAutomata) {
    for (auto terminateState : this->automata.get_terminateStates()) {
      for (auto state : mapHelper) {
        for (auto value : state.second) {
          if (std::stoi(terminateState->getTag()) == value) {
            newAutomata.setTerminateState(std::to_string(state.first));
            return;
          }
        }
      }
    }
  }

  void setTransitions(std::map<int, std::set<int>> &mapHelper, Af &newAutomata) {
    for (auto state : mapHelper) {
      for (auto &letter : newAutomata.getAlphabet()) {
        auto it = state.second.begin(); //mover up
        int singleState = (*it); // mover up
        auto a = this->automata.getTransition(std::to_string(singleState), letter);

        bool timeToBreak = false;
        for (auto stateToFind : mapHelper) {
          if (timeToBreak) {
            break;
          }

          for (auto value : stateToFind.second) {
            if (value == std::stoi(a->get_end()->getTag())) {
              // 4, no 6.
              newAutomata.addTransition(std::to_string(state.first), letter, std::to_string(stateToFind.first));
              timeToBreak = true;
              break;
            }
          }
        }
      }
    }
  }
};

#endif
