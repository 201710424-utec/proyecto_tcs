#include "Af.h"
#include "Brz.h"
#include "algorithms/StateEquivalence.h"
#include "State.h"

int main() {
  Af afd;
  afd.buildFromConsole();

  auto * seq = new StateEquivalence{afd};
  seq->fillTable();
  seq->describe();

  return 0;
}
