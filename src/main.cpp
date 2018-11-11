#include "Af.h"
#include "Brz.h"

int main() {
  Af afd;
  afd.buildFromConsole();

  Brz *brz = new Brz{afd};
  brz->reversing();
  brz->afd();
  brz->optimize();
  brz->remakeAutomata();
  brz->reversing();
  brz->afd();
  brz->optimize();
  brz->getAutomata().describe();std::cout<<'\n';


  return 0;
}



