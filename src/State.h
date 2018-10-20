#include <vector>
class State{
public:
    int tag;
    std::vector<State*> one;
    std::vector<State*> zero;
    std::vector<State*> epsilon;
    bool finish;
    
State()= default;
~State();


};