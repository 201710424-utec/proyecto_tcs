#ifndef READ_H
#define READ_H

#include "Af.h"
#include <iostream>

class Read {
 private:
  Af readAfd;

  std::string pieceLineRead(std::string &lineRead) {
    std::size_t posSpace = lineRead.find(" ");
    if (posSpace != std::string::npos) {
      std::string piece = lineRead.substr(0, posSpace);
      lineRead = lineRead.substr(++posSpace);
      return piece;
    } else {
      std::string piece = lineRead;
      return piece;
    }
  }

 public:
  Read() {
    std::string lineRead;
    int numberStates = 0;
    std::string startStateTag;
    std::string finishStateTag;
    int numberFinishStates = 0;
    std::string exitState, transitionVar, arrivalState;
    std::getline(std::cin, lineRead);
    numberStates = std::stoi(pieceLineRead(lineRead));
    (this->readAfd).setNumberStates(numberStates);
    startStateTag = pieceLineRead(lineRead);
    (this->readAfd).setStartState(startStateTag);
    numberFinishStates = std::stoi(pieceLineRead(lineRead));
    for (size_t i = 0; i < numberFinishStates; i++) {
      finishStateTag = pieceLineRead(lineRead);
      (this->readAfd).setFinishState(finishStateTag);
    }
    for (size_t i = 0; i < (2 * numberStates); i++) {
      std::getline(std::cin, lineRead);
      exitState = pieceLineRead(lineRead);
      transitionVar = pieceLineRead(lineRead);
      arrivalState = pieceLineRead(lineRead);
      (this->readAfd).addTransition(exitState, transitionVar, arrivalState);
    }
  }

  inline Af getAfd() { return this->readAfd; }
};

#endif
