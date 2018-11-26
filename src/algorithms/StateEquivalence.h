#ifndef PROYECTO_TCS_STATEEQUIVALENCE_H
#define PROYECTO_TCS_STATEEQUIVALENCE_H

#include <vector>
#include <iostream>
#include "../models/Af.h"
#include "../models/State.h"
#include "../helpers/TransitionHelper.h"

class StateEquivalence {
 private:
  Af automata;
  std::map<std::string, std::map<std::string, bool>> equivalenceMatrix;
  TransitionHelper *transitions = nullptr;
  bool equivalent = true;

 public:
  explicit StateEquivalence(Af automata) {
    this->automata = automata;
  }

  void fillTable() {
    this->createMatrix();
    this->baseCase();
    this->fillTransitions();
    this->inductiveStep();
  }

  void createMatrix() {
    for (auto &firstState : this->automata.get_states()) {
      for (auto &secondState : this->automata.get_states()) {
        this->equivalenceMatrix[firstState.second->getTag()][secondState.second->getTag()] = true;
      }
    }
  }

  void fillTransitions() {
    this->transitions = new TransitionHelper(this->automata);
  }

  void baseCase() {
    for (auto &terminateState : this->automata.get_terminateStates()) {
      for (auto &state : this->automata.get_States()) {
        if (!state.second->isTerminateState()) {
          this->equivalenceMatrix[terminateState->getTag()][state.second->getTag()] = false;
          this->equivalenceMatrix[state.second->getTag()][terminateState->getTag()] = false;
        }
      }
    }
  }

  void inductiveStep() {
    bool touch = true;
    while (touch) {
      touch = false;
      for (auto &state : this->automata.get_states()) {
        for (auto compareState : this->automata.get_states()) {
          if (state.first != compareState.first) {
            for (auto &letter : this->automata.getAlphabet()) {
              auto r = this->transitions->getFirst(state.first, letter);
              auto s = this->transitions->getFirst(compareState.first, letter);

              if (!this->equivalenceMatrix[r][s]) {
                if (this->equivalenceMatrix[state.second->getTag()][compareState.second->getTag()]) {
                  touch = true;
                  this->equivalenceMatrix[state.second->getTag()][compareState.second->getTag()] = !this->equivalent;
                  this->equivalenceMatrix[compareState.second->getTag()][state.second->getTag()] = !this->equivalent;
                }
              }
            }
          }
        }
      }
    }
  }

  void describe() {
    for (auto &state : this->equivalenceMatrix) {
      for (auto &list : state.second) {
          std::cout << list.second << " ";
      }
      std::cout << std::endl;
    }
  }
};

#endif //PROYECTO_TCS_STATEEQUIVALENCE_H
