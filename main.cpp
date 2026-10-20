#include "instance.h"
#include "random_search.h"
#include "neh.h"
#include "genetic_algorithm.h"
#include "metrics.h"
#include "experiments.h"

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
  int upper_bound = -1;

  std::string first_line; 
  std::getline(input, first_line);
  std::istringstream first_stream(first_line);
  if(first_stream >> jobs >> machines) {
    upper_bound = -1;
  } else {
    std::string data_line;
    std::getline(input, data_line);
    std::istringstream data_stream(data_line);

    int initial_seed;
    int lower_bound;

    data_stream >> jobs >> machines >> initial_seed
                >> upper_bound >> lower_bound;
    
    //Skip header line
    std::string processing_header;
    std::getline(input, processing_header);
  }

  std::vector<std::vector<int>> processing_times(machines, std::vector<int>(jobs));

  for(int machine = 0; machine < machines; machine++) {
    for(int job = 0; job < jobs; job++) {
      input >> processing_times[machine][job];
    }
  }

Instance instance(jobs, machines, processing_times, upper_bound);

runExperiments(instance, argv[1]);

return 0;

}