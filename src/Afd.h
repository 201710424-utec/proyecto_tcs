#include <vector>
#include "State.h"
class Afd{
public:
std::vector<State *> states; 

    Afd()=default;
    ~Afd();
};