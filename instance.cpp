#include "instance.h"
#include <vector>
#include <algorithm>


int Instance::makespan(const std::vector<int>& permutation) const {
  std::vector<std::vector<int>> times(static_cast<int>(permutation.size()) + 1, std::vector<int>(machines_ + 1, 0));

  for (int i = 1; i <= static_cast<int>(permutation.size()); ++i) {
    for (int j = 1; j <= machines_; ++j) {
      times[i][j] = std::max(times[i - 1][j], times[i][j - 1]) +
                    processing_times_[j - 1][permutation[i - 1] - 1];
    }
  }

  return times[permutation.size()][machines_];
}  
