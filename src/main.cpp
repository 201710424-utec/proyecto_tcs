#include "algorithms/Brz.h"
#include "algorithms/StateEquivalence.h"
#include "algorithms/MatrixEquivalences.h"
#include "algorithms/Moore.h"
#include "algorithms/Hopcroft.h"

int main() {
  Af afd;
  afd.buildFromConsole();

  // Brzozowski
  Brz *brz = new Brz{afd};
  brz->execute();
  brz->getAutomata().describe();

  // Equivalencia de estados
  auto *seq = new StateEquivalence{afd};
  seq->fillTable();
  seq->describe();

  // Versión mejorada del algoritmo de equivalencia de estadados
  MatrixEquivalences matrixEquivalences(afd);
  matrixEquivalences.describe();

  // Moore
  auto *moore = new Moore<int>(afd, matrixEquivalences.getMatrix());
  moore->exec();
  moore->describe();

  // Hopcroft
  Hopcroft *hop = new Hopcroft(afd);
  hop->execute().describe();

  return 0;
}
