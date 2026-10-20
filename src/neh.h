#ifndef NEH_H_
#define NEH_H_

#include <vector>
#include "instance.h"

class NEH {
  public:

  void run(const Instance& instance);

  const std::vector<int>& getBestPermutation() const {
    return best_permutation_;
  }

  int getBestMakespan() const {
    return best_makespan_;
  }

  private:
    std::vector<int> best_permutation_;
    int best_makespan_;
};

#endif