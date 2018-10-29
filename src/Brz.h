#ifndef BRZ_H
#define BRZ_H

#include "Af.h"

class Brz {
 private:
  Af automata;
 public:

  Brz() = default;
  Brz(Af automata) {
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
};

#endif
