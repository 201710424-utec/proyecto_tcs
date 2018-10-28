#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>

class State {
 public:
  std::string tag;

  friend std::ostream &operator<<(std::ostream &stream, const State &state) {
    return stream << state.tag;
  }

  State() = default;
  ~State() = default;
};

#endif 
