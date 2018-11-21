#ifndef BRZ_H
#define BRZ_H
#include "../models/Af.h"
#include <string>
#include <cmath>
#include <map>
#include "../helpers/TransitionHelper.h"
#include <algorithm>
#include <vector>
#include <stack>
#include <sstream>

class Brz {

 private:
  Af automata;
  TransitionHelper *transition;

 public:
  Brz() = default;
  explicit Brz(const Af &automata) {
    this->automata = automata;
  }

  Af getAutomata() const {
    return this->automata;
  }

  /**
   * hacemos swap de las transiciones y estados finales e iniciales
   */
  void reversing() {
    this->automata.get_initialStates().swap(this->automata.get_terminateStates());
    for (auto &i : this->automata.get_transitions()) {
      i->swap();
    }
    this->transition = new TransitionHelper(this->automata);
    this->transition->sortVector();
    std::cout << '\n';
  }

  static std::string cast(char c) {
    std::stringstream ss;
    std::string s;
    ss << c;
    ss >> s;
    return s;
  }

  bool in(std::vector<std::string> vec, std::string a) {
    for (auto &i : vec) {
      if (a == i) {
        return true;
      }
    }
    return false;
  }

  void sortString(std::string &str) {
    std::sort(str.begin(), str.end());
  }

  void get(std::string str, std::string res, std::vector<std::string> &vec) {
    sortString(res);
    if (!in(vec, res) && res != "") {
      sortString(res);
      vec.push_back(res);
    }
    for (int i = 0; i < str.length(); i++)
      get(std::string(str).erase(i, 1), res + str[i], vec);
  }

  bool in_string(std::string word, std::string letter) {
    int cont = 0;

    for (auto &i : word) {
      if (cast(i) == letter) {
        return true;
      }
    }
    return false;
  }

  std::string reach(std::string word, std::string character) {
    std::string extra = "";
    for (auto &letter : word) {
      for (auto &final :this->transition->get(cast(letter), character)) {
        if (!in_string(extra, final) && final != "$") {
          extra += final;
        }
      }
    }

    if (!extra.empty()) {
      sortString(extra);
      return extra;
    } else {
      return "$";
    }
  }

  /**
   * Función que convierte el automata AFN a AFD
   */
  void afd() {
    for (auto &character : this->automata.getAlphabet()) {
      for (auto &state : this->automata.get_States()) {
        if (this->transition->get(state.first, character).empty()) {
          this->transition->set(state.first, character, "$");
        }
      }
    }

    std::string initialState;
    for (auto &state : this->automata.get_initialStates()) {
      initialState += state->getTag();
    }
    sortString(initialState);

    std::string endState;
    for (auto &state : this->automata.get_terminateStates()) {
      endState = state->getTag();
    }
    sortString(endState);

    TransitionHelper *extraHelper = new TransitionHelper();
    std::vector<std::string> visited;
    std::stack<std::string> stack;
    stack.push(initialState);

    while (!stack.empty()) {
      std::string initial = stack.top();
      visited.push_back(initial);
      auto h = stack.top();
      stack.pop();

      for (auto &character : this->automata.getAlphabet()) {
        std::string reaching = reach(initial, character);
        extraHelper->set(initial, character, reaching);
        if (!in(visited, reaching)) {
          sortString(reaching);
          stack.push(reaching);
          visited.push_back(reaching);
        }
      }
    }
    this->transition = extraHelper;

    Af newAutomata;
    int cont = 0;
    for (auto &state : this->transition->get_map()) {
      cont++;
      newAutomata.addState(state.first);
    }
    newAutomata.setInitialState(initialState);
    newAutomata.setNumberStates(cont);

    for (auto &state : newAutomata.get_States()) {
      if (in_string(state.first, endState)) {
        newAutomata.setTerminateState(state.first);
      }
    }

    for (auto &state : newAutomata.get_States()) {
      for (auto &alpha : this->automata.getAlphabet()) {
        for (auto &final : this->transition->get(state.first, alpha))
          newAutomata.addTransition(state.first, alpha, final);
      }
    }

    newAutomata.setAllAlphabet(this->automata.getAlphabet());
    this->automata = newAutomata;
  }

  /**
   * Despues de tomar los estados alcanzables , cambiamos los nombres de los estados para ua mejor comprensión
   */
  void remakeAutomata() {
    Af newautomata;
    int cont = 0;
    auto letter = '0';
    std::map<std::string, std::string> auxiliarMap;

    for (auto &i : this->automata.get_States()) {
      auxiliarMap[i.first] = cast(static_cast<char>(letter + cont));
      cont++;
      newautomata.addState(auxiliarMap[i.first]);
    }

    newautomata.setAllAlphabet(this->automata.getAlphabet());

    for (auto &j : this->automata.get_transitions()) {
      newautomata.addTransition(auxiliarMap[j->get_begin()->getTag()],
                                j->get_caracter(),
                                auxiliarMap[j->get_end()->getTag()]);
    }

    for (auto &k : this->automata.get_initialStates()) {
      newautomata.addInitialState(auxiliarMap[k->getTag()]);
    }

    for (auto &l : this->automata.get_terminateStates()) {
      newautomata.addTerminateState(auxiliarMap[l->getTag()]);
    }

    newautomata.setNumberStates(this->automata.get_numberStates());
    this->automata = newautomata;
  }

  void execute() {

    this->reversing();
    this->afd();
    this->remakeAutomata();
    this->reversing();
    this->afd();
    this->remakeAutomata();
  }

};

#endif