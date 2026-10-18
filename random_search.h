#ifndef RANDOM_SEARCH_H_
#define RANDOM_SEARCH_H_

#include <vector>
#include <random>
#include "instance.h"

class RandomSearch {
  public:

  explicit RandomSearch(unsigned int seed) : generator_(seed) {}

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
    std::mt19937 generator_;
};


#endif