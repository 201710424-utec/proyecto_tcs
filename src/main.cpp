#include "models/Af.h"
#include "algorithms/Brz.h"
#include "algorithms/StateEquivalence.h"
#include "algorithms/MatrixEquivalences.h"
#include "models/State.h"

int main() {
  Af afd;
  afd.buildFromConsole();

  Brz *brz = new Brz{afd};
  brz->execute();
  brz->getAutomata().describe();

   auto * seq = new StateEquivalence{afd};
   seq->fillTable();
   seq->describe();

   MatrixEquivalences matrixEquivalences(afd);
   matrixEquivalences.describe();

  return 0;
}
