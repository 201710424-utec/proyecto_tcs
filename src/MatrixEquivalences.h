#ifndef MATRIXEQUIVALENCES_H
#define MATRIXEQUIVALENCES_H

#include "Af.h"
#include "helpers/MatrixEquivalencesPixel.h"
#include "helpers/TransitionHelper.h"
#include <vector>
#include <map>
#include <queue>
#include <iostream>

class MatrixEquivalences {
private:
  std::vector<std::vector<MatrixEquivalencesPixel>> matrix;
  std::map<std::string, int> headers;
public:
  MatrixEquivalences(Af originAutomata) {
    TransitionHelper delta(originAutomata);
    std::queue<std::vector<int>> discoveredPairs;
    std::vector<std::string> alphabet = originAutomata.getAlphabet();
    this->matrix.resize(originAutomata.get_numberStates());
    for (size_t i = 0; i < this->matrix.size(); i++) {
      this->matrix[i].resize(originAutomata.get_numberStates());
    }
    {
      int i = 0;
      for (std::map<std::string, State *>::iterator it = originAutomata.get_States().begin(); it != originAutomata.get_States().end(); it++, i++) {
        this->headers[it->first] = i;
      }
    }
    for (std::map<std::string, State *>::iterator itx = originAutomata.get_States().begin(); itx != originAutomata.get_States().end(); itx++) {
      for (std::map<std::string, State *>::iterator ity = originAutomata.get_States().begin(); ity != originAutomata.get_States().end(); ity++) {
        for (std::vector<std::string>::iterator itAlphabet = alphabet.begin(); itAlphabet != alphabet.end(); itAlphabet++) {
          std::string nextStateX = delta.get(itx->first, *itAlphabet)[0];
          std::string nextStateY = delta.get(ity->first, *itAlphabet)[0];
          this->matrix[this->headers[nextStateX]][this->headers[nextStateY]].addDependentPair({this->headers[itx->first],this->headers[ity->first]});
          this->matrix[this->headers[nextStateX]][this->headers[nextStateY]].addDependentPair({this->headers[ity->first],this->headers[itx->first]});
          this->matrix[this->headers[nextStateY]][this->headers[nextStateX]].addDependentPair({this->headers[itx->first],this->headers[ity->first]});
          this->matrix[this->headers[nextStateY]][this->headers[nextStateX]].addDependentPair({this->headers[ity->first],this->headers[itx->first]});
        }
      }
      for (std::map<std::string, State *>::iterator itx = originAutomata.get_States().begin(); itx != originAutomata.get_States().end(); itx++) {
        for (std::map<std::string, State *>::iterator ity = originAutomata.get_States().begin(); ity != originAutomata.get_States().end(); ity++) {
          if (originAutomata.isTerminateState(itx->second) != originAutomata.isTerminateState(ity->second)) {
            this->matrix[this->headers[itx->first]][this->headers[ity->first]].setValue(0);
            this->matrix[this->headers[ity->first]][this->headers[itx->first]].setValue(0);
            for (auto itDependetPairs = (this->matrix[this->headers[itx->first]][this->headers[ity->first]].getDependentPairs()).begin(); itDependetPairs != (this->matrix[this->headers[itx->first]][this->headers[ity->first]].getDependentPairs()).end(); itDependetPairs++) {
              if (this->matrix[(*itDependetPairs)[0]][(*itDependetPairs)[1]].getValue() == 1) {
                this->matrix[(*itDependetPairs)[0]][(*itDependetPairs)[1]].setValue(0);
                this->matrix[(*itDependetPairs)[1]][(*itDependetPairs)[0]].setValue(0);
                discoveredPairs.push({(*itDependetPairs)[0],(*itDependetPairs)[1]});
                discoveredPairs.push({(*itDependetPairs)[1],(*itDependetPairs)[0]});
              }
            }
            this->checkDiscoveredPairs(discoveredPairs);
          }
        }
      }
    }
  }

  void checkDiscoveredPairs(std::queue<std::vector<int>> &discoveredPairs) {
    while (!discoveredPairs.empty()) {
      for (auto itDependetPairs = (this->matrix[discoveredPairs.front()[0]][discoveredPairs.front()[1]].getDependentPairs()).begin(); itDependetPairs != (this->matrix[discoveredPairs.front()[0]][discoveredPairs.front()[1]].getDependentPairs()).end(); itDependetPairs++) {
        if (this->matrix[(*itDependetPairs)[0]][(*itDependetPairs)[1]].getValue() == 1) {
          this->matrix[(*itDependetPairs)[0]][(*itDependetPairs)[1]].setValue(0);
          this->matrix[(*itDependetPairs)[1]][(*itDependetPairs)[0]].setValue(0);
          discoveredPairs.push({(*itDependetPairs)[0],(*itDependetPairs)[1]});
          discoveredPairs.push({(*itDependetPairs)[1],(*itDependetPairs)[0]});
        }
      }
      discoveredPairs.pop();
    }
  }

  void describe () {
    std::cout << '\n';
    for (std::map<std::string, int>::iterator ity = this->headers.begin(); ity != this->headers.end(); ity++) {
      std::cout << '\t' << ity->first;
    }
    std::cout << '\n';
    for (std::map<std::string, int>::iterator itx = this->headers.begin(); itx != this->headers.end(); itx++) {
      std::cout << itx->first << '\t';
      for (std::map<std::string, int>::iterator ity = this->headers.begin(); ity != this->headers.end(); ity++) {
        std::cout << (this->matrix[itx->second][ity->second]).getValue() <<'\t';
      }
      std::cout << '\n';
    }
  }

};

#endif //MATRIXEQUIVALENCES_H
