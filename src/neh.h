#ifndef NEH_H_
#define NEH_H_

#include <vector>
#include "instance.h"

/**
 * @brief Implements the NEH heuristic for the PFSP.
 *
 * NEH is a deterministic constructive heuristic. It orders the jobs by their
 * total processing time and then builds the final permutation by inserting
 * each job in the position that produces the lowest makespan.
 */
class NEH {
  public:

  /**
   * @brief Executes the NEH heuristic on a PFSP instance.
   *
   * The method constructs a job permutation progressively and stores the best
   * permutation and its corresponding makespan.
   *
   * @param instance PFSP instance to solve.
   */
  void run(const Instance& instance);

  /**
   * @brief Returns the best permutation found.
   *
   * @return Reference to the best job permutation.
   */
  const std::vector<int>& getBestPermutation() const {
    return best_permutation_;
  }

  /**
   * @brief Returns the makespan of the best solution found.
   *
   * @return Best makespan.
   */
  int getBestMakespan() const {
    return best_makespan_;
  }

  private:
    std::vector<int> best_permutation_;
    int best_makespan_;
};

#endif