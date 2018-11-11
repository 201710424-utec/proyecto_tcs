#ifndef BRZ_H
#define BRZ_H

#include "Af.h"
#include <sstream>
#include <string>
#include <math.h>
#include <map>
#include "helpers/TransitionHelper.h"
#include <algorithm>
#include <stack>

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

  void reversing() {
    this->automata.get_initialStates().swap(this->automata.get_terminateStates());
    for (auto &i : this->automata.get_transitions()) {
      i->swap();
    }
    this->transition = new TransitionHelper(this->automata);
    this->transition->sortVector();
    //this->transition->describe();
  }

  static std::string cast(char c) {
    std::stringstream ss;
    std::string s;

    ss << c;
    ss >> s;
    return s;
  }

  void sortString(std::string &str) {
    std::sort(str.begin(), str.end());
  }

  bool in(std::string word, const std::string &character) {
    for (auto &i: word) {
      if (cast(i) == character) {
        return true;
      }
    }
    return false;
  }

  void afd() {

    std::string state;
    std::string final;
    std::vector<std::string> vec;
    for (auto &i: this->automata.get_States()) {
      final += i.first;
    }
    int cont = 1;
    auto iter = this->automata.get_States().begin();


    /*  for(auto &i :this->automata.get_States() ){
        for(auto &j :this->automata.get_States() ){
          std::cout<<i.first<<" "<<j.first<<'\n';
        }
      }
  */
    auto iter2 = this->automata.get_States().begin();

    for (; iter != this->automata.get_States().end(); iter++) {
      iter2 = iter;

      for (iter2++; iter2 != this->automata.get_States().end(); iter2++) {

        state = iter->first + iter2->first;
        this->sortString(state);
        vec.push_back(state);

        state = "";
      }

    }

    vec.push_back(final);
    vec.push_back("$");

    /*  for(auto &state : vec){
        this->automata.addState(state);
      }
  */
    /* for (auto &i : vec) {
       std::cout << i << " ";
     }
 */

    //############################### vector finished #######################
    std::string extra;
    for (auto &character : this->automata.getAlphabet()) {

      for (auto &statex : vec) {

        for (auto &letter : statex) {

          if (!this->transition->get(cast(letter), character).empty()) {

            for (auto &finalState : this->transition->get(cast(letter), character)) {

              if (!in(extra, finalState)) {

                extra += finalState;
                this->sortString(extra);

              }

            }

          }

        }
        if (extra.empty()) {
          this->transition->set(statex, character, "$");
        } else {
          this->sortString(extra);

          this->transition->set(statex, character, extra);
        }

        extra = "";
      }
    }

    for (auto &character : this->automata.getAlphabet()) {
      for (auto &state : this->automata.get_States()) {
        if (this->transition->get(state.first, character).empty()) {
          this->transition->set(state.first, character, "$");
        }
      }
    }

    for (auto &state1 : vec) {
      this->sortString(state1);
      this->automata.addState(state1);
    }

//    this->transition->describe();

    std::string newInitialState;
    for (auto &state2 : this->automata.get_initialStates()) {
      newInitialState += state2->getTag();
    }

    this->sortString(newInitialState);
    this->automata.get_initialStates().clear();
    this->automata.setInitialState(newInitialState);
    //this->transition->describe();

    std::cout << '\n';
  }


//###############################################################################################

  void optimize() {

    Af newAutomata;
    std::stack<std::string> stackStates;
    for (auto &state : this->automata.get_initialStates()) {
      newAutomata.setInitialState(state->getTag());
      stackStates.push(state->getTag());
    }
    int contador = 0;
    while (!stackStates.empty()) {
      auto state = stackStates.top();

      stackStates.pop();
      contador++;
      for (auto &letter : this->automata.getAlphabet()) {
        std::string newFinalState;
        auto arrivalStates = this->transition->get(state, letter);
        for (auto &arrivalState : arrivalStates) {
          newFinalState+=arrivalState;
        }
        if (!newAutomata.in(newFinalState)) {

          newAutomata.addState(newFinalState);
          stackStates.push(newFinalState);
        }

        newAutomata.addTransition(state, letter, newFinalState);
        newFinalState="";

      }
    }
    for (auto &state:this->automata.get_terminateStates()) {
      for (auto &state2:newAutomata.get_States()) {
        if (in(state2.first, state->getTag())) {
          newAutomata.setTerminateState(state2.first);
        }
      }
    }
    newAutomata.setNumberStates(contador);
    newAutomata.setAllAlphabet(this->automata.getAlphabet());
    this->automata = newAutomata;
    //this->transition->describe();
    this->transition->clear();

  }

  //#############################################################################


  void remakeAutomata() {
    Af newautomata;
    int cont = 0;
    auto letter = 'x';
    std::map<std::string, std::string> auxiliarMap;
    for (auto &i : this->automata.get_States()) {

      auxiliarMap[i.first] = cast(static_cast<char>(letter + cont));
      cont++;
      newautomata.addState(auxiliarMap[i.first]);
      //std::cout<<auxiliarMap[i.first]<<'\n';
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
  void changeStateNames() {
    int cont = 0;
    for (auto &state : this->automata.get_States()) {
      state.second->changeTag((std::to_string(cont)));
      cont++;
    }
  }



























  /*
   static std::string cast(char c) {
     std::stringstream ss;
     std::string s;

     ss << c;
     ss >> s;
     return s;
   }
   std::string *get_transition(std::string tag) {
     std::string *arr = new std::string[2];
     std::string zero;
     std::string one;
     std::vector<Transition *> vec = automata.get_transitions();
     for (auto &i : tag) {

       for (auto &j : vec) {
         if (j->get_begin()->getTag() == cast(i)) {
           (j->get_caracter() == "0") ? zero += j->get_end()->getTag() : one += j->get_end()->getTag();
         }
       }
     }
     arr[0] = zero;
     arr[1] = one;

     return arr;
   }
   void afd() {

   }
   bool in(Af automata, std::string Tag) {
     auto iter = automata.get_States().begin();
     for (; iter != automata.get_States().end(); iter++) {
       if (iter->first == Tag) {
         return true;
       }
     }
     return false;
   }
   bool has_transitions(std::string initialTag) {
     for (auto &i : this->automata.get_transitions()) {
       if (i->get_begin()->getTag() == initialTag) {
         return true;
       }
     }
     return false;
   }
   void add_reachable_states(Af newautomata, std::string initialTag) {
     while (has_transitions(initialTag)) {
       for (auto &i : this->automata.get_transitions()) {
         if (i->get_begin()->getTag() == initialTag) {
           newautomata.addState(i->get_end()->getTag());
           initialTag = i->get_end()->getTag();
           add_reachable_states(newautomata, initialTag);
         }
       }
     }
   }
   void addTransitions(Af newautomata, std::string initialTag) {
     for (auto &i : this->automata.get_transitions()) {
       if (i->get_begin()->getTag() == initialTag) {
         newautomata.addTransition(i->get_begin()->getTag(), i->get_caracter(), i->get_end()->getTag());
       }
     }
   }

   void optimize() {

     Af newautomata;
     newautomata.addState(this->automata.get_single_initialState()->getTag());
     std::string initialTag = this->automata.get_single_initialState()->getTag();
     add_reachable_states(newautomata, initialTag);
     auto iter = newautomata.get_States().begin();
     for (; iter != newautomata.get_States().end(); ++iter) {
       addTransitions(newautomata, iter->first);
     }

     this->automata = newautomata;
   }


   // describe only for tests

   void describe_test() {
     auto iter = automata.get_States().begin();
     for (; iter != automata.get_States().end(); iter++) {
       std::cout << iter->first << " ";
     }

   }
 */
};

#endif
