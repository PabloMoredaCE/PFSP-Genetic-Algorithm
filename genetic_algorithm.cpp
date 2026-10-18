#include "genetic_algorithm.h"
#include <algorithm>
#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(int population_size, double pc, double pm, 
      int tournament_size, unsigned int seed) :
        population_size_(population_size), pc_(pc), pm_(pm), tournament_size_(tournament_size), generator_(seed) {}



void GeneticAlgorithm::run(const Instance& instance, int evaluations) {
  population_.clear();

  for(int i = 0; i < population_size_; ++i) {
    std::vector<int> individual(instance.getJobs());

    std::iota(individual.begin(), individual.end(), 1);
    std::shuffle(individual.begin(), individual.end(), generator_);

    int make = instance.makespan(individual);
    population_.push_back({individual, make});
  }

  for (int i = 0; i < 5; ++i) {
  int winner = tournamentSelection();

  std::cout << "Tournament winner: "
            << winner
            << " Makespan: "
            << population_[winner].second
            << '\n';
}
}


int GeneticAlgorithm::tournamentSelection() {
  std::uniform_int_distribution<int> distribution(0, static_cast<int>(population_.size()) - 1);

  int best_index = distribution(generator_);

  for(int i = 1; i < tournament_size_; ++i) {
    int candidate_index = distribution(generator_);

    if(population_[candidate_index].second < population_[best_index].second) {
      best_index = candidate_index;
    }
  }

  return best_index;
}