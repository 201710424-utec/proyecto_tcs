#ifdef READ_H
#define READ_H

#include "afd.h"
#include <iostream>


class Read {
private:
  afd readAfd;

  std::string pieceLineRead(std::string &lineRead) {
    std::size_t posSpace = lineRead.find(" ");
    if (posSpace != std::string::npos) {
      std::string piece = lineRead.substr(0,posSpace);
      lineRead = lineRead.substr(++posSpace);
      return piece;
    }else{
      std::string piece = lineRead;
      return piece;
    }
  }

public:
  Read() {
    std::string lineRead = "";
    int numberStates = 0, startState = 0;
    int numberFinishStates = 0, finishState = 0;
    int exitState = 0, transitionVar = 0, arrivalState = 0;
    std::getline(std::cin, lineRead);
    numberStates = std::stoi(pieceLineRead(lineRead));
    (this->readAfd).setNumberStates(numberStates);
    startState = std::stoi(pieceLineRead(lineRead));
    (this->readAfd).setStartState(startState);
    numberFinishStates = std::stoi(pieceLineRead(lineRead));
    for (size_t i = 0; i < numberFinishStates; i++) {
      finishState = std::stoi(pieceLineRead(lineRead));
      (this->readAfd).addFinishState(finishState);
    }
    for (size_t i = 0; i < (2*numberStates); i++) {
      lineRead = std::getline(std::cin, lineRead);
      exitState = std::stoi(pieceLineRead(lineRead));
      transitionVar = std::stoi(pieceLineRead(lineRead));
      arrivalState = std::stoi(pieceLineRead(lineRead));
      (this->readAfd).addTransition(exitState,transitionVar,arrivalState);
    }
  }

  afd getAfd() {return this->readAfd}
};

#endif
