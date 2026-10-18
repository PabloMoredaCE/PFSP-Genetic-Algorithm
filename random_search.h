#ifndef RANDOM_SEARCH_H_
#define RANDOM_SEARCH_H_

#include <vector>
#include "instance.h"

class RandomSearch {
  public:

  void run(const Instance& instance, int evaluations);

  std::vector<int> random_permutation(int jobs);

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