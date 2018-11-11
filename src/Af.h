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
  std::vector<std::string> alphabet;
 public:

  void addState(std::string newState) {
    this->states[newState] = new State{newState};
  }

  void setNumberStates(int numberStates) {
    this->numberStates = numberStates;
  }

  void setInitialState(const std::string &startStateTag) {
    this->states[startStateTag] = new State{startStateTag};
    this->initialStates.push_back(this->states[startStateTag]);
  }

  void setTerminateState(const std::string &finishStateTag) {
    this->states[finishStateTag] = new State{finishStateTag};
    this->terminateStates.push_back(this->states[finishStateTag]);
  }

  void addTerminateState(const std::string &finishStateTag) {
    this->terminateStates.push_back(this->states[finishStateTag]);
  }
  void addInitialState(const std::string &initialStateTag) {
    this->initialStates.push_back(this->states[initialStateTag]);
  }

  void addTransition( std::string departureState,  std::string caracter,  std::string arrivalState) {
    auto *newTransition = new Transition{this->states[departureState], this->states[arrivalState], caracter};
    this->transitions.push_back(newTransition);
  }

  bool in(std::string stateTest) {
    for (auto &i: this->states) {
      if (i.first == stateTest) {
        return true;
      }
    }
    return false;
  }

  void buildFromConsole() {
    // Definition helpers
    std::string initialState;
    std::string numTerminalStates;
    std::string terminateState;

    // Transitions helpers
    std::string departureState;
    std::string transitionCaracter;
    std::string arrivalState;

    // alphabet helper
    std::map<std::string, std::string *> alphabetHelper;

    // First line
    std::cin >> this->numberStates >> initialState >> numTerminalStates;

    this->setInitialState(initialState);
    this->states[initialState] = new State{initialState};

    // Terminate states
    for (int i = 0; i < std::stoi(numTerminalStates); ++i) {
      std::cin >> terminateState;
      this->setTerminateState(terminateState);

      if (!this->states[terminateState]) {
        this->states[terminateState] = new State{terminateState};
      }
    };

    // Read 2n transitions
    for (int j = 0; j < 2 * this->numberStates; ++j) {
      std::cin >> departureState >> transitionCaracter >> terminateState;

      if (!this->states[departureState]) {
        this->addState(departureState);
      }

      if (!this->states[terminateState]) {
        this->addState(terminateState);
      }

      if (!alphabetHelper[transitionCaracter]) {
        alphabetHelper[transitionCaracter] = new std::string{transitionCaracter};
        this->setAlphabet(transitionCaracter);
      }

      auto *transition = new Transition{this->states[departureState], this->states[terminateState], transitionCaracter};
      this->transitions.push_back(transition);
    }
  }

  void setAlphabet(const std::string &letter) {
    this->alphabet.push_back(letter);
  }

  std::vector<std::string> getAlphabet() {
    return this->alphabet;
  }

  void describe() {
    // First line: number of states, initial states, number of terminate states, terminate states
    // Total number of states
    std::cout << this->numberStates << " ";

    // Initial states
    for (auto &initialState : this->initialStates) {
      std::cout << initialState->getTag() << " ";
    }

    // Total number of terminate states
    std::cout << this->terminateStates.size() << " ";

    // Terminate states
    for (auto &terminateState : this->terminateStates) {
      std::cout << terminateState->getTag() << " ";
    }

    std::cout << std::endl;
    // 2n line: Transitions
    for (auto &transition : this->transitions) {
      std::cout << transition->get_begin()->getTag() << " " << transition->get_caracter() << " "
                << transition->get_end()->getTag() << std::endl;
    }
  }

  int get_numberStates() {
    return numberStates;
  }
  std::map<std::string, State *> &get_States() {
    return this->states;
  }

  std::vector<State *> &get_initialStates() {
    return this->initialStates;
  }

  std::vector<State *> &get_terminateStates() {
    return this->terminateStates;
  }

  std::vector<Transition *> get_transitions() {
    return this->transitions;
  }
  State *get_single_initialState() {
    return this->initialStates[0];
  }

  Af() = default;
  ~Af() = default;
};

#endif
