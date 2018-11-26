#include "models/Af.h"
#include "algorithms/Brz.h"
#include "algorithms/Hopcroft.h"
#include "algorithms/StateEquivalence.h"
#include "algorithms/MatrixEquivalences.h"
#include "models/State.h"

int main() {
  Af afd;
  afd.buildFromConsole();

  std::cout <<'\n' << "---------------------------------------------" << '\n';

  Hopcroft *hop = new Hopcroft(afd);
  hop->execute().describe();


  // Brz *brz = new Brz{afd};
  // brz->execute();
  // brz->getAutomata().describe();
  //
  // auto * seq = new StateEquivalence{afd};
  // seq->fillTable();
  // seq->describe();
  //
  // MatrixEquivalences matrixEquivalences(afd);
  // matrixEquivalences.describe();

  return 0;
}
