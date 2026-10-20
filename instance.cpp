#include "instance.h"
#include <vector>
#include <algorithm>


int Instance::makespan(const std::vector<int>& permutation) const {
  std::vector<int> times(machines_ + 1, 0);

  for (int job : permutation) {
    for (int machine = 1; machine <= machines_; ++machine) {
      times[machine] = std::max(times[machine], times[machine - 1]) +
                    processing_times_[machine - 1][job - 1];
    }
  }

  return times[machines_];
}  
