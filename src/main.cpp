#include "Af.h"
#include "Brz.h"

int main() {
  Af afd;
  afd.buildFromConsole();

  Brz *brz = new Brz{afd};
  brz->reversing();

  brz->getAutomata().describe();
  return 0;
}
