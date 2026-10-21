#ifndef RANDOM_SEARCH_H_
#define RANDOM_SEARCH_H_

#include <vector>
#include <random>
#include "instance.h"

/**
 * @brief Implements a Random Search algorithm for the PFSP.
 *
 * The algorithm repeatedly generates random job permutations and evaluates
 * their makespan until the evaluation budget is exhausted.
 */
class RandomSearch {
  public:

  /**
   * @brief Constructs a Random Search algorithm.
   *
   * @param seed Seed used by the pseudo-random number generator.
   */
  explicit RandomSearch(unsigned int seed);

  /**
   * @brief Executes Random Search on a PFSP instance.
   *
   * Random permutations are generated and evaluated until the specified
   * number of makespan evaluations has been performed.
   *
   * @param instance PFSP instance to solve.
   * @param evaluations Maximum number of makespan evaluations.
   */
  void run(const Instance& instance, int evaluations);

  /**
   * @brief Generates a random permutation of jobs.
   *
   * @param jobs Number of jobs in the permutation.
   * @return Random permutation containing all jobs exactly once.
   */
  std::vector<int> random_permutation(int jobs);

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


  /**
   * @brief Returns the convergence history of the algorithm.
   *
   * Each pair contains the number of evaluations performed and the best
   * makespan found up to that point.
   *
   * @return Convergence history.
   */
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