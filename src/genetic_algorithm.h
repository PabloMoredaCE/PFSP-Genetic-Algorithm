#ifndef GENETIC_ALGORITHM_H_
#define GENETIC_ALGORITHM_H_

#include <random>
#include <vector>
#include <utility>
#include "instance.h"

class GeneticAlgorithm {
    
  public:
    GeneticAlgorithm(int population_size, double pc, double pm, 
      int tournament_size, unsigned int seed);
    
    void run(const Instance& instance, int evaluations);

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
    int population_size_;
    double pc_;
    double pm_;
    int tournament_size_;
    std::mt19937 generator_;
    
    std::vector<std::pair<int, int>> convergence_;

    std::vector<int> best_permutation_;
    int best_makespan_;


    std::vector<std::pair<std::vector<int>, int>> population_;

    int tournamentSelection();

    std::vector<int> orderCrossover(const std::vector<int>& parent1, const std::vector<int>& parent2);

    void swapMutation(std::vector<int>& individual);
    void insertionMutation(std::vector<int>& individual);

    bool isValidPermutation(const std::vector<int>& permutation, int jobs) const;

};
#endif