#include "models/Af.h"
#include "algorithms/Brz.h"
#include "algorithms/Hopcroft.h"
#include "algorithms/StateEquivalence.h"
#include "algorithms/MatrixEquivalences.h"
#include "models/State.h"
#include <ctime>

int main() {
  Af afd;
  afd.buildFromConsole();

  std::cout <<'\n' << "---------------------------------------------" << '\n';

  Hopcroft *hop = new Hopcroft(afd);
  clock_t  clock1,clock2;
  clock1 = clock();
  hop->execute().describe();
  clock2 = clock();
  std::cout <<'\n' << "---------------------------------------------" << '\n';
  std::cout<< "Hopcroft time "<< (float)(clock2 - clock1)/ CLOCKS_PER_SEC*1000 << " "<<'\n';


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
