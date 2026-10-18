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

  const std::vector<int>& parent1 = population_[0].first;
const std::vector<int>& parent2 = population_[1].first;

std::vector<int> child = orderCrossover(parent1, parent2);

std::cout << "Parent 1: ";
for (int job : parent1) {
  std::cout << job << ' ';
}

std::cout << "\nParent 2: ";
for (int job : parent2) {
  std::cout << job << ' ';
}

std::cout << "\nChild: ";
for (int job : child) {
  std::cout << job << ' ';
}

std::cout << '\n';

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

std::vector<int> GeneticAlgorithm::orderCrossover(const std::vector<int>& parent1, const std::vector<int>& parent2) {
  int size = static_cast<int>(parent1.size());
  std::vector<int> child(size);
  std::uniform_int_distribution<int> distribution(0, size - 1);

  int cut1 = distribution(generator_);
  int cut2 = distribution(generator_);
  if(cut1 > cut2) {
    int temp = cut1;
    cut1 = cut2;
    cut2 = temp;
  }
 
  for(int i = cut1; i <= cut2; ++i) {
    child[i] = parent1[i];
  }

  int child_pos = (cut2 + 1) % size;
  for(int offset = 1; offset <= size; ++offset) {
    int parent_pos = (cut2 + offset) % size;
    int job = parent2[parent_pos];

    if(std::find(child.begin(), child.end(), job) == child.end()) {
      child[child_pos] = job;
      child_pos = (child_pos + 1) % size;
    }
  }
  return child;
  
}