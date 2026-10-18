#include "instance.h"
#include "random_search.h"
#include "neh.h"
#include "genetic_algorithm.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

/**
 * @file main.cpp
 * @brief Inicio del programa
 * 
 */

int main(int argc, char* argv[]) {

  if(argc != 3 && argc != 7) {
    std::cerr << "Usage: "
              << "  " << argv[0] << "<input_file> <seed>\n"
              << "  " << argv[0] 
              << " <input_file> <seed> <population> <pc> <pm> <tournament>\n"; 
    return 1;
  }

  std::ifstream input{argv[1]};

  if (!input) {
    std::cerr << "Couldn't open file\n";
    return 1;
  }

  unsigned int seed = static_cast<unsigned int>(std::stoul(argv[2]));
  int population_size = 50;
  double pc = 0.8;
  double pm = 0.1;
  int tournament_size = 3;

  if(argc == 7) {
    population_size = std::stoi(argv[3]);
    pc = std::stod(argv[4]);
    pm = std::stod(argv[5]);
    tournament_size = std::stoi(argv[6]);
  }

  if(population_size <= 0) {
    std::cerr << "Population size must be positive\n";
    return 1;
  }

  if(pc < 0.0 || pc > 1.0 || pm < 0.0 || pm > 1.0) {
    std::cerr << "pc and pm must be between 0 and 1\n";
    return 1;
  }

  if(tournament_size <= 0 || tournament_size > population_size) {
    std::cerr << "Invalid tournament size\n";
    return 1;
  } 

  int jobs;
  int machines;
  
  input >> jobs >> machines;
  std::vector<std::vector<int>> processing_times(machines, std::vector<int>(jobs));

  for(int machine = 0; machine < machines; machine++) {
    for(int job = 0; job < jobs; job++) {
      input >> processing_times[machine][job];
    }
  }

Instance instance(jobs, machines, processing_times);

RandomSearch rands(seed);
rands.run(instance, 2);
  std::cout << "Random Makespan 2: " << rands.getBestMakespan();
  std::cout << '\n';
  for (int job : rands.getBestPermutation()) {std::cout << job << ' ';}
  std::cout << '\n';

rands.run(instance, 10000);
  std::cout << "Random Makespan 10000: " << rands.getBestMakespan();
  std::cout << '\n';
  for (int job : rands.getBestPermutation()) {std::cout << job << ' ';}
  std::cout << '\n';

NEH neh;
neh.run(instance);
  std::cout << "NEH Makespan: " << neh.getBestMakespan();
  std::cout << '\n';
  for (int job : neh.getBestPermutation()) {std::cout << job << ' ';}
  std::cout << '\n';

GeneticAlgorithm gen(population_size, pc, pm, tournament_size, seed);
gen.run(instance, 50000);

std::cout << "Genetic Algorithm Makespan: "
          << gen.getBestMakespan()
          << '\n';

for (int job : gen.getBestPermutation()) {
  std::cout << job << ' ';
}

std::cout << '\n';

return 0;

}