#include "Af.h"
#include "Brz.h"
#include "MatrixEquivalences.h"

int main() {
  Af afd;
  afd.buildFromConsole();
  MatrixEquivalences matrixEquivalences(afd);
  matrixEquivalences.describe();
  return 0;
}
