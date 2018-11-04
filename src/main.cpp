#include "Af.h"
#include "Brz.h"

int main() {
  Af afd;
  afd.buildFromConsole();

  Brz *brz = new Brz{afd};
  brz->reversing();
  brz->afd();
  brz->optimize();
  brz->reversing();
  brz->afd();
  brz->optimize();

  //brz->describe_test();
  return 0;
}
