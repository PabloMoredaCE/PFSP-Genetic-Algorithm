#include "genetic_algorithm.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

GeneticAlgorithm::GeneticAlgorithm(int population_size, double pc, double pm, 
      int tournament_size, unsigned int seed, double pls) :
        population_size_(population_size), pc_(pc), pm_(pm), 
        tournament_size_(tournament_size), generator_(seed), pls_(pls), best_makespan_(std::numeric_limits<int>::max()) {}



void GeneticAlgorithm::run(const Instance& instance, int evaluations) {
  population_.clear();
  convergence_.clear();
  best_permutation_.clear();
  best_makespan_ = std::numeric_limits<int>::max();

  int evaluation_count = 0;
  int best_so_far = std::numeric_limits<int>::max();

  for(int i = 0; i < population_size_; ++i) {
    std::vector<int> individual(instance.getJobs());

    std::iota(individual.begin(), individual.end(), 1);
    std::shuffle(individual.begin(), individual.end(), generator_);

    if(!isValidPermutation(individual, instance.getJobs())) {
      throw std::runtime_error("Invalid permutation in initial population");
    }

    int make = instance.makespan(individual);
    ++evaluation_count;
    population_.push_back({individual, make});

    if(make < best_so_far) {
      best_so_far = make;
    }

    if(evaluation_count % 1000 == 0 || evaluation_count == evaluations) {
      convergence_.push_back({evaluation_count, best_so_far});
    }
  }

  std::uniform_real_distribution<double> probability(0.0, 1.0);
  std::uniform_int_distribution<int> mutation_type(0, 1);

  while(evaluation_count < evaluations) {
    std::vector<std::pair<std::vector<int>, int>> new_population;

    int elite_index = 0;
    for(int i = 1; i < static_cast<int>(population_.size()); ++i) {
      if(population_[i].second < population_[elite_index].second) {
        elite_index = i;
      }
    }

    auto elite = population_[elite_index]; 


    while((new_population.size() < static_cast<std::size_t>(population_size_)) && (evaluation_count < evaluations)) {

      int parent1_index = tournamentSelection();
      int parent2_index = tournamentSelection();

      const std::vector<int>& parent1 = population_[parent1_index].first;
      const std::vector<int>& parent2 = population_[parent2_index].first;

      std::vector<int> child1;
      std::vector<int> child2;

      //Crossover
      if(probability(generator_) < pc_) {
        child1 = orderCrossover(parent1, parent2);
        child2 = orderCrossover(parent2, parent1);
      } else {
        child1 = parent1;
        child2 = parent2;
      }

      //Mutation 1
      if (probability(generator_) < pm_) {
        if (mutation_type(generator_) == 0) {
        swapMutation(child1);
        } else {
          insertionMutation(child1);
        }
      }

      //Mutation 2
      if (probability(generator_) < pm_) {
        if (mutation_type(generator_) == 0) {
          swapMutation(child2);
        } else {
          insertionMutation(child2);
        }
      }

      if(!isValidPermutation(child1, instance.getJobs())) {
        throw std::runtime_error("Invalid permutation for child1");
      }
      if(!isValidPermutation(child2, instance.getJobs())) {
        throw std::runtime_error("Invalid permutation for child2");
      }

      //Evaluation 1
      int make1 = instance.makespan(child1);
      ++evaluation_count;

      if(make1 < best_so_far) {
        best_so_far = make1;
      }

      if(evaluation_count % 1000 == 0 || evaluation_count == evaluations) {
        convergence_.push_back({evaluation_count, best_so_far});
      }

      if(pls_ > 0.0 && evaluation_count < evaluations && probability(generator_) < pls_) {
        insertionLocalSearch(child1, make1, instance, evaluation_count, evaluations, best_so_far);

        if(!isValidPermutation(child1, instance.getJobs())) {
          throw std::runtime_error("Invalid permutation after local search for child1");
        }
      }

      new_population.push_back({child1, make1});


      //Evaluation 2 (if there is space)
      if((new_population.size() < static_cast<std::size_t>(population_size_)) && (evaluation_count < evaluations)) {
        int make2 = instance.makespan(child2);
        ++evaluation_count;

        if(make2 < best_so_far) {
        best_so_far = make2;
        }

      if(evaluation_count % 1000 == 0 || evaluation_count == evaluations) {
        convergence_.push_back({evaluation_count, best_so_far});
      }

      if(pls_ > 0.0 && evaluation_count < evaluations && probability(generator_) < pls_) {
        insertionLocalSearch(child2, make2, instance, evaluation_count, evaluations, best_so_far);

        if(!isValidPermutation(child2, instance.getJobs())) {
          throw std::runtime_error("Invalid permutation after local search for child1");
        }
      }

      new_population.push_back({child2, make2});
      } 
    }

    int worst_index = 0;
    for(int i = 1; i < static_cast<int>(new_population.size()); ++i) {
      if(new_population[i].second > new_population[worst_index].second) {
        worst_index = i;
      }
    }

    if(elite.second < new_population[worst_index].second) {
      new_population[worst_index] = elite;
    }

    population_ = new_population;
  }

  int best_index = 0;

  for (int i = 1; i < static_cast<int>(population_.size()); ++i) {
    if (population_[i].second < population_[best_index].second) {
      best_index = i;
    }
  }

  best_permutation_ = population_[best_index].first;
  best_makespan_ = population_[best_index].second;
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


void GeneticAlgorithm::swapMutation(std::vector<int>& individual) {
  if(individual.size() < 2) { return; }
  std::uniform_int_distribution<int> distribution(0, static_cast<int>(individual.size()) - 1);

  int pos1 = distribution(generator_);
  int pos2 = distribution(generator_);

  while(pos1 == pos2) {
    pos2 = distribution(generator_);
  }
  
  std::swap(individual[pos1], individual[pos2]);
}


void GeneticAlgorithm::insertionMutation(std::vector<int>& individual) {
  if(individual.size() < 2) { return; }
  std::uniform_int_distribution<int> distribution(0, static_cast<int>(individual.size()) - 1);

  int from = distribution(generator_);
  int to = distribution(generator_);

  while(from == to) {
    to = distribution(generator_);
  }
  
  int job = individual[from];
  individual.erase(individual.begin() + from);
  individual.insert(individual.begin() + to, job);
}

bool GeneticAlgorithm::isValidPermutation(const std::vector<int>& permutation, int jobs) const {
  if(jobs != static_cast<int>(permutation.size())) {
    return false;
  }

  for(int i = 1; i <= jobs; ++i) {
    int count = 0;
    for(int j = 0; j < jobs; ++j) {
      if(permutation[j] == i) { ++count; };
    }
    if(count != 1) {
      return false;
    }
  }
  return true;
}

void GeneticAlgorithm::insertionLocalSearch(std::vector<int>& individual, int& makespan,
      const Instance& instance, int& evaluation_count, int max_evaluations,
      int& best_so_far, int forced_postion) {
        if(individual.size() < 2) { return; }

        int size = static_cast<int>(individual.size());
        int from;

        if(forced_postion != -1) {
          if(forced_postion < 0 || forced_postion >= size) {
            throw std::invalid_argument("Invalid forced position");
          }

          from = forced_postion;
        } else {
          std::uniform_int_distribution<int> distribution(0, size - 1);
          from = distribution(generator_);
        }

        int job = individual[from];
        std::vector<int> partial = individual;
        partial.erase(partial.begin() + from);
        
        std::vector<int> best_individual = individual;
        int best_make = makespan;

        for(int position = 0; position < size; ++position) {
          if(position == from) { continue; }
          if(evaluation_count >= max_evaluations) { break; }

          std::vector<int> candidate = partial;
          candidate.insert(candidate.begin() + position, job);

          int candidate_make = instance.makespan(candidate);

          ++evaluation_count;

          if(candidate_make < best_so_far) {
            best_so_far = candidate_make;
          }

          if(evaluation_count % 1000 == 0 || evaluation_count == max_evaluations) {
            convergence_.push_back({evaluation_count, best_so_far});
          }

          if(candidate_make < best_make) {
            best_make = candidate_make;
            best_individual = candidate;
          }
        }

        if(!isValidPermutation(best_individual, instance.getJobs())) {
          throw std::runtime_error("Invalid permutation after local search");
        }

        individual = best_individual;
        makespan = best_make;
      
      
}