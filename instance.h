#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <vector>

class Instance {
  public:

    Instance(int jobs, int machines, const std::vector<std::vector<int>>& processing_times) :
      jobs_(jobs), machines_(machines), processing_times_(processing_times) {
    }

  /**
   * @brief Returns the makespan of a given permutación
   * @param permutation Order of execution of jobs
   * @return Makespan of the sequence
   */
  int makespan(const std::vector<int>& permutation) const;  

  int getJobs() const {
    return jobs_;
  }

  int getMachines() const {
    return machines_;
  }

  int getProcessingTime(int machine, int job) const {
    return processing_times_[machine][job];
  }

  private:
    int jobs_;
    int machines_;
    std::vector<std::vector<int>> processing_times_;

};

#endif