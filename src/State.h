#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>

class State {
 public:
  std::string tag;

  std::string getTag() const {
    return this->tag;
  }

  bool operator==(const State &stateToCompare) {
    return this->tag == stateToCompare.getTag();
  }

  friend std::ostream &operator<<(std::ostream &stream, const State &state) {
    return stream << state.tag;
  }

  State() = default;
  ~State() = default;
};

#endif 
