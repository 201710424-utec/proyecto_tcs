#ifndef BRZ_H
#define BRZ_H

#include "Af.h"

class Brz {
 private:
  Af automata;
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
  }

  void afd() {
    Af newautomata;
    auto it = automata.get_States().begin();

    // setting the singular states(can it be simplify?)

    for (; it != automata.get_States().end(); it++) {
      //std::cout<<it->first<<'\n';
      newautomata.addState(it->first);

    }

    // setting up all the combined states
    auto cont = automata.get_numberStates();
    auto it2 = automata.get_States().begin();
    auto it3 = automata.get_States().begin();

    for (; it2 != automata.get_States().end()--; it2++) {

      it3 = it2;

      for (it3++; it3 != automata.get_States().end(); it3++) {

        newautomata.addState(it2->first + it3->first);

      }
    }

    //setting up the last state

    std::string lastState;
    auto it4 = automata.get_States().begin();

    for (; it4 != automata.get_States().end(); it4++) {

      lastState += it4->first;

    }

    newautomata.addState(lastState);
    this->automata = newautomata;

    //########################## end of the States push ##########################



  }
  //################################ describe only for tests ###########################

  void describe_test() {
    auto iter = automata.get_States().begin();
    for (; iter != automata.get_States().end(); iter++) {
      std::cout << iter->first << " ";
    }

  }

  //#####################################################################################
};

#endif
