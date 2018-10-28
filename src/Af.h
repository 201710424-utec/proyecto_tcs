#ifndef AF_H
#define AF_H

#include <iostream>
#include <vector>
#include <map>
#include "State.h"
#include "Transition.h"

class Af {
 private:
  int numberStates;
  std::map<std::string, State *> states;
  std::vector<Transition *> transitions;
  std::vector<State *> initialStates;
  std::vector<State *> terminateStates;

 public:
  void addState(std::string newState) {
    State *state = new State{newState};
    this->states[newState] = state;
  }

  void setNumberStates(int numberStates) {
    this->numberStates = numberStates;
  }

  void setStartState(std::string startStateTag) {
    this->initialStates.push_back(this->states[startStateTag]);
  }

  void setFinishState(std::string finishStateTag) {
    this->terminateStates.push_back(this->states[finishStateTag]);
  }

  void addTransition(const std::string exitState, const std::string transitionVar, const std::string arrivalState) {
    auto *begin = new State{exitState};
    auto *end = new State{arrivalState};

    auto *newTransition = new Transition{begin, end, transitionVar};
    this->transitions.push_back(newTransition);
  }

  void buildFromConsole() {
    // Definition helpers
    std::string initialState;
    std::string numTerminalStates;
    std::string terminateState;

    // Transitions helpers
    std::string departureState;
    std::string transitionCharacter;
    std::string arrivalState;

    // First line
    std::cin >> this->numberStates >> initialState >> numTerminalStates;

    auto *tempInitialState = new State{initialState};
    this->initialStates.push_back(tempInitialState);
    this->states[tempInitialState->tag] = tempInitialState;

    for (int i = 0; i < std::stoi(numTerminalStates); ++i) {
      std::cin >> terminateState;
      auto *tempTerminateState = new State{terminateState};
      this->terminateStates.push_back(tempTerminateState);

      if (!this->states[terminateState]) {
        this->states[terminateState] = tempTerminateState;
      }
    };

    std::cout << this->numberStates << " " << this->initialStates[0]->tag << " " << numTerminalStates << " "
              << this->terminateStates.size() << std::endl;

    // Read 2n transitions
    for (int j = 0; j < 2 * this->numberStates; ++j) {
      std::cin >> departureState >> transitionCharacter >> terminateState;

      if (!this->states[departureState]) {
        auto *tempDepartureState = new State{departureState};
        this->states[departureState] = tempDepartureState;
      }

      if (!this->states[terminateState]) {
        auto *tempTerminateState = new State{terminateState};
        this->states[terminateState] = tempTerminateState;
      }

      auto
          *transition = new Transition{this->states[departureState], this->states[terminateState], transitionCharacter};
      this->transitions.push_back(transition);
    }
  }

  Af() = default;
  ~Af() = default;
};

#endif
