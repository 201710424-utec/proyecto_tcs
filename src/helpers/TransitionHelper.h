#include <utility>
#include <vector>
#include <algorithm>

#ifndef PROYECTO_TCS_TRANSITIONHELPER_H
#define PROYECTO_TCS_TRANSITIONHELPER_H

#include "../Af.h"

class TransitionHelper {
  std::map<std::string, std::map<std::string, std::vector<std::string> >> transitions;

 public:
  void sortString(std::string &str) {
    std::sort(str.begin(), str.end());
  }
  TransitionHelper(Af automata) {
    for (auto &transition : automata.get_transitions()) {
      std::string value = transition->get_end()->getTag();
      this->sortString(value);
      std::string value2 = transition->get_begin()->getTag();
      this->sortString(value2);
      this->transitions[value2][transition->get_caracter()].push_back(value);


    }
  }
  void sortVector(){
    for(auto &r :  this->transitions){
      for(auto &k : r.second){
        std::sort(k.second.begin(),k.second.end());
      }
    }
  }
  ~TransitionHelper(){
    this->transitions.clear();
  };

  void set(const std::string &state, const std::string &character, std::string endState) {
    this->transitions[state][character].push_back(std::move(endState));
  }

  std::vector<std::string> get(std::string state, std::string character) {
    return this->transitions[state][character];
  }

  std::map<std::string, std::vector<std::string>> getMap2(std::string state) {
    return this->transitions[state];
  }

  void clear(){
    this->transitions.clear();
  }

  void describe() {
    for (auto t : this->transitions) {
      std::cout << t.first << std::endl;
      for (auto &i : t.second) {
        std::cout << i.first << " -> ";
        for (auto &r :i.second) {

          std::cout << r;
        }
        std::cout << '\n';
      }
      std::cout << "\n";
    }
    std::cout << '\n';
  }
};

#endif //PROYECTO_TCS_TRANSITIONHELPER_H

