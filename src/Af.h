#ifndef AF_H
#define AF_H

#include <vector>
#include <map>
#include "State.h"
#include "Transition.h"

class Af {
 private:
  std::map<std::string, State *> states;
  std::vector<Transition *> transitions;
  int numberStates;
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

  std::vector<State *> get_initialStates() {
    return this->initialStates;
  }

  std::vector<State *> get_terminateStates() {
    return this->terminateStates;
  }

  std::vector<Transition *> get_transitions() {
    return this->transitions;
  }

  Af() = default;
  ~Af();
};

#endif
