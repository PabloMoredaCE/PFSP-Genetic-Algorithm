#include "neh.h"
#include "instance.h"

#include <utility>
#include <algorithm>


void NEH::run(const Instance& instance) {
  int jobs = instance.getJobs();
  std::vector<int> total(jobs, 0);
  std::vector<std::pair<int, int>> job_times(jobs);

  for(int i = 0; i < jobs; ++i) {
    for(int j = 0; j < instance.getMachines(); ++j) {
      total[i] += instance.getProcessingTime(j, i);
    }
    job_times[i].first = i + 1;
    job_times[i].second = total[i];
  }

  std::sort(job_times.begin(), job_times.end(), 
    [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
      return a.second > b.second;
    });

  std::vector<int> first_order{job_times[0].first, job_times[1].first};
  int first_make = instance.makespan(first_order);

  std::vector<int> second_order{job_times[1].first, job_times[0].first};
  int second_make = instance.makespan(second_order);

  if(first_make < second_make) {
    best_makespan_ = first_make;
    best_permutation_ = first_order;
  } else {
    best_makespan_ = second_make;
    best_permutation_ = second_order;
  }

  for(int k = 2; k < jobs; ++k) {
    int job = job_times[k].first;

    std::vector<int> best_candidate;
    int best_candidate_make = 0;

    for (int pos = 0; pos <= static_cast<int>(best_permutation_.size()); ++pos) {
      std::vector<int> candidate = best_permutation_;

      candidate.insert(candidate.begin() + pos, job);
      int make = instance.makespan(candidate);

      if (pos == 0 || make < best_candidate_make) {
        best_candidate = candidate;
        best_candidate_make = make;
      }
    }

    best_permutation_ = best_candidate;
    best_makespan_ = best_candidate_make;
  }

}