#include "instance.h"
#include "random_search.h"
#include "neh.h"

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

  if(argc != 3) {
    std::cerr << "Usage: "
              << argv[0]
              << " <input_file> <seed>\n"; 
    return 1;
  }

  std::ifstream input{argv[1]};

  unsigned int seed = static_cast<unsigned int>(std::stoul(argv[2]));

  if (!input) {
    std::cerr << "Couldn't open file\n";
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

}