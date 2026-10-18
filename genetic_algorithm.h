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


  private:
    int population_size_;
    int tournament_size_;
    double pc_;
    double pm_;

    std::mt19937 generator_;

    std::vector<std::pair<std::vector<int>, int>> population_;

    int tournamentSelection();
};
#endif