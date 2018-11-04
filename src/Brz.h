#ifndef BRZ_H
#define BRZ_H

#include "Af.h"
#include <sstream>
#include <string>

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

  static std::string cast(char c){
    std::stringstream ss;
    std::string s;

    ss << c;
    ss >> s;
    return s;
  }
  std::string* get_transition(std::string tag){
    std::string *arr = new std::string [2];
    std::string zero;
    std::string one;
    std::vector<Transition *> vec = automata.get_transitions();
    for(auto &i : tag){

      for(auto &j : vec){
        if(j->get_begin()->getTag()==cast(i)){
          (j->get_caracter()=="0")? zero+=j->get_end()->getTag() : one+=j->get_end()->getTag();
        }
      }
    }
    arr[0]=zero;
    arr[1]=one;

    return arr;
  }
  void afd() {
    Af newautomata;

    //################## pushing states ################################

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
    newautomata.addState("$");



    // ###############################################################



    //###################### make transitions #############################

    auto it5=newautomata.get_States().begin();
    std::string * ptr;
    for(;it5!=newautomata.get_States().end();it5++){
      ptr=get_transition(it5->first);
      if(ptr[0].size()!=0){
        newautomata.addTransition(it5->first,"0",ptr[0]);
      }
      else{
        newautomata.addTransition(it5->first,"0","$");
      }
      if(ptr[1].size()!=0){
        newautomata.addTransition(it5->first,"0",ptr[1]);
      }
      else{
        newautomata.addTransition(it5->first,"0","$");
      }
    }

    //################################################################



  }

  void optimize(){

  }


  // describe only for tests

  void describe_test() {
    auto iter = automata.get_States().begin();
    for (; iter != automata.get_States().end(); iter++) {
      std::cout << iter->first << " ";
    }

  }

};

#endif
