#ifndef RANDOM_SEARCH_H_
#define RANDOM_SEARCH_H_

#include <vector>
#include <random>
#include "instance.h"

class RandomSearch {
  public:

  explicit RandomSearch(unsigned int seed);

  void run(const Instance& instance, int evaluations);

  std::vector<int> random_permutation(int jobs);

  const std::vector<int>& getBestPermutation() const {
    return best_permutation_;
  }

  int getBestMakespan() const {
    return best_makespan_;
  }

  const std::vector<std::pair<int, int>>& getConvergence() const {
    return convergence_;
  }

  private:
    std::vector<int> best_permutation_;
    std::mt19937 generator_;
    int best_makespan_;

    std::vector<std::pair<int, int>> convergence_;
};


#endif