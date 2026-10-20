#include "instance.h"
#include "instance_reader.h"
//#include "random_search.h"
#include "neh.h"
#include "genetic_algorithm.h"
#include "metrics.h"
#include "experiments.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * @file main.cpp
 * @brief Inicio del programa
 * 
 */
void printPermutation(const std::vector<int>& permutation) {
  for(int job : permutation) {
    std::cout << job << ' ';
  }
  std::cout << '\n';
}

int main(int argc, char* argv[]) {

  if(argc == 2 && std::string(argv[1]) == "-r") {
    resetRawResults();
    return 0;
  }

   if (argc == 3 && std::string(argv[1]) == "-e") {
    try {
      std::string filename = argv[2];
      
      Instance instance = loadInstance(filename);
      runExperiments(instance, filename);
    } catch (const std::exception& error) {
      std::cerr << error.what() << '\n';
      return 1;
    }

    return 0;
  }

    if(argc == 4 && std::string(argv[1]) == "-g") {
    int jobs = std::stoi(argv[2]);
    int machines = std::stoi(argv[3]);

    try {
      runExperimentGroup(jobs, machines);
    } catch (const std::exception& error) {
      std::cerr << error.what() << '\n';
      return 1;
    }
    return 0;
  }

  if (argc != 3 && argc != 7) {

    std::cerr << "Usage:\n" << "  " << argv[0]
              << " <input_file> <seed>\n"
              << "  " << argv[0] << " <input_file> <seed>"
              << " <population> <pc> <pm> <tournament>\n"
              << "  " << argv[0] << " -e <input_file>\n"
              << "  " << argv[0] << " -r\n"
              << "  " << argv[0] << " -g <jobs> <machines>\n";
    return 1;
  }


  std::string filename = argv[1];

  unsigned int seed = static_cast<unsigned int>(std::stoul(argv[2]));

  // Default parameters
  int population_size = 50;
  double pc = 0.8;
  double pm = 0.1;
  int tournament_size = 3;

  // Custom parameters
  if (argc == 7) {
    population_size = std::stoi(argv[3]);
    pc = std::stod(argv[4]);
    pm = std::stod(argv[5]);
    tournament_size = std::stoi(argv[6]);
  }

  // Parameter validation
  if (population_size <= 0) {
    std::cerr << "Population size must be positive\n";
    return 1;
  }

  if (pc < 0.0 || pc > 1.0 || pm < 0.0 || pm > 1.0) {
    std::cerr << "pc and pm must be between 0 and 1\n";
    return 1;
  }

  if (tournament_size <= 0 || tournament_size > population_size) {
    std::cerr << "Invalid tournament size\n";
    return 1;
  }


  try {
    Instance instance = loadInstance(filename);
    GeneticAlgorithm gen(population_size, pc, pm, tournament_size, seed);
    gen.run(instance, 50000);

    std::cout << "Genetic Algorithm Makespan: " << gen.getBestMakespan() << '\n';
    printPermutation(gen.getBestPermutation());

    // Instance information
    std::cout << "Jobs: " << instance.getJobs() << '\n';
    std::cout << "Machines: " << instance.getMachines() << '\n';
    std::cout << "UB: " << instance.getUpperBound() << '\n';

    std::cout << "Result " << seed << ' ' << population_size << ' ' << pc << ' ' << pm << ' '
              << tournament_size << ' ' << gen.getBestMakespan() << ' ' 
              << calculateRPD(gen.getBestMakespan(), instance.getUpperBound()) << '\n';
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }

  return 0;
}