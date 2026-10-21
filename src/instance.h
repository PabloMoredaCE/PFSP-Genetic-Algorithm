#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <vector>

/**
 * @brief Represents an instance of the Permutation Flow Shop Problem (PFSP)
 * Stores number of jovs, machines, processing times and upper bound
 */
class Instance {
  public:
    /**
     * @brief Constructs a PFSP instance.
     *
     * @param jobs Number of jobs in the instance.
     * @param machines Number of machines in the instance.
     * @param processing_times Matrix containing the processing times.
     *        The first index represents the machine and the second the job.
     * @param upper_bound Known upper bound for the instance.
     *        Defaults to -1 when no upper bound is available.
     */
    Instance(int jobs, int machines, 
      const std::vector<std::vector<int>>& processing_times, int upper_bound = -1) :
        jobs_(jobs), machines_(machines), processing_times_(processing_times), 
        upper_bound_(upper_bound) {}

  /**
   * @brief Returns the makespan of a given permutación
   * @param permutation Order of execution of jobs
   * @return Makespan of the sequence
   */
  int makespan(const std::vector<int>& permutation) const;  

  /**
   * @brief Getter for jobs
   * 
   * @return Number of jobs in the instance
   */
  int getJobs() const {
    return jobs_;
  }

  /**
   * @brief Getter for machines
   * 
   * @return Number of machines in the instance
   */
  int getMachines() const {
    return machines_;
  }

  /**
   * @brief Getter for processing times
   * 
   * @param machine Machine index
   * @param job Job index
   * @return Processing time of the job (index) on the machine
   */
  int getProcessingTime(int machine, int job) const {
    return processing_times_[machine][job];
  }

  /**
   * @brief Getter for upper bound
   * 
   * @return Upper bound, or -1
   */
  int getUpperBound() const {
    return upper_bound_;
  }

  private:
    int jobs_;
    int machines_;
    std::vector<std::vector<int>> processing_times_;
    int upper_bound_;

};

#endif