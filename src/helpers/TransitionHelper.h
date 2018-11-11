#include <utility>

#ifndef PROYECTO_TCS_TRANSITIONHELPER_H
#define PROYECTO_TCS_TRANSITIONHELPER_H

#include "../Af.h"

class TransitionHelper {
  std::map<std::string, std::map<std::string, std::vector<std::string>>> transitions;

 public:
  TransitionHelper(Af automata) {
    for (auto &transition : automata.get_transitions()) {
      this->transitions[transition->get_begin()->getTag()][transition->get_caracter()].push_back(transition->get_end()->getTag());
    }
  }

  void set(const std::string &state, const std::string &character, std::string endState) {
    this->transitions[state][character].push_back(endState);
  }

  std::vector<std::string> get(std::string state, std::string character) {
    return this->transitions[state][character];
  }

  std::string getFirst(std::string state, std::string character) {
    return this->get(state, character)[0];
  }
};

#endif //PROYECTO_TCS_TRANSITIONHELPER_H
