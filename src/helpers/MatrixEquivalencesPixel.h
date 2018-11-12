#ifndef PROYECTO_TCS_MATRIXEQUIVALENCESPIXEL_H
#define PROYECTO_TCS_MATRIXEQUIVALENCESPIXEL_H

#include <list>
#include <vector>

class MatrixEquivalencesPixel {
private:
  int value = 1;
  std::list<std::vector<int>> dependentPairs;
public:
  MatrixEquivalencesPixel() {}

  void setValue(int newValue) {
    this->value = newValue;
  }

  int getValue() {
    return this->value;
  }

  void addDependentPair(std::vector<int> pair) {
    this->dependentPairs.push_back(pair);
  }

  std::list<std::vector<int>> &getDependentPairs() {
    return this->dependentPairs;
  }

  ~MatrixEquivalencesPixel() {}

};

#endif //PROYECTO_TCS_MATRIXEQUIVALENCESPIXEL_H
