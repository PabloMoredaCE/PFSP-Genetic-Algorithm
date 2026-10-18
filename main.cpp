#include "instance.h"

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

  if(argc != 2) {
    std::cerr << "Usage: "
              << argv[0]
              << " <input_file>\n"; 
    return 1;
  }

  std::ifstream input{argv[1]};

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
