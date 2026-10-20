#include "random_search.h"
#include <algorithm>
#include <numeric>
#include <limits>

  RandomSearch::RandomSearch(unsigned int seed) : generator_(seed), best_makespan_(std::numeric_limits<int>::max()) {}

  std::vector<int>RandomSearch::random_permutation(int jobs) {
    std::vector<int> permutation(jobs);
    
    std::iota(permutation.begin(), permutation.end(), 1);
    std::shuffle(permutation.begin(), permutation.end(), generator_);

    return permutation;

  }

  void RandomSearch::run(const Instance& instance, int evaluations) {
    best_permutation_.clear();
    best_makespan_ = std::numeric_limits<int>::max();
    convergence_.clear();

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
      
      int evaluation = i + 1;
      if(evaluation % 1000 == 0 || evaluation == evaluations) {
        convergence_.push_back({evaluation, best_makespan_});
      }
    }
  }

