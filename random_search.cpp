#include "random_search.h"
#include <algorithm>
#include <numeric>
#include <random>


  std::vector<int>RandomSearch::random_permutation(int jobs) {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::vector<int> permutation(jobs);
    
    std::iota(permutation.begin(), permutation.end(), 1);
    std::shuffle(permutation.begin(), permutation.end(), engine);

    return permutation;

  }

  void RandomSearch::run(const Instance& instance, int evaluations) {
    for(int i = 0; i < evaluations; ++i) {
      std::vector<int> permutation = random_permutation(instance.getJobs());
      int makespan = instance.makespan(permutation);

      if(i == 0) {
        best_permutation_ = permutation;
        best_makespan_ = makespan;
        continue;
      }

      if(makespan < best_makespan_) {
        best_permutation_ = permutation;
        best_makespan_ = makespan;
      }
    }
  }

