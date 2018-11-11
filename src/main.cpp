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
/*
3 0 2 1 2
0 0 1
0 1 0
1 0 2
1 1 0
2 0 2
2 1 0



3 x 2 y z
x a z
x b x
y a y
y b x
z a y
z b x

 */