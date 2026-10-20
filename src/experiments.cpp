#include "experiments.h"
#include "genetic_algorithm.h"
#include "metrics.h"
#include "neh.h"
#include "instance_reader.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <algorithm>
#include <numeric>

void runExperiments(const Instance& instance, const std::string& instance_name, int population_size, double pc, double pm, int tournament_size) {
  bool file_exists = std::ifstream("raw_results.csv").good();
  std::ofstream output("raw_results.csv", std::ios::app);

  if(!output) {
    std::cerr << "Could not create file raw_results.csv\n";
    return;
  }

  if(!file_exists) {
    output << "Instance,n,m,Algorithm,Run,Seed,"
           << "Population,pc,pm,Tournament,"
           << "Cmax,CPU,RPD(UB)\n";
  }

  //Parameter definition
  unsigned int base_seed = 42;


  for (int run = 0; run < 10; ++run) {
    unsigned int seed = base_seed + run;
    GeneticAlgorithm ga(population_size, pc, pm, tournament_size, seed);

    auto start = std::chrono::high_resolution_clock::now();
    ga.run(instance, 50000);

    auto end = std::chrono::high_resolution_clock::now();

    double seconds = std::chrono::duration<double>(end - start).count();

    int cmax = ga.getBestMakespan();

    double rpd_ub = calculateRPD(cmax, instance.getUpperBound());

     output << instance_name << ',' << instance.getJobs() << ',' << instance.getMachines() << ','
         << "GA" << ',' << run + 1 << ',' << seed << ','
         << population_size << ',' << pc << ',' << pm << ',' << tournament_size << ','
         << cmax << ',' << seconds << ',' << rpd_ub << '\n';
  }
}

void resetRawResults() {
  if(std::filesystem::remove("raw_results.csv")) {
    std::cout << "raw_results.csv reset sucessfully\n";
  } else {
    std::cout << "raw_results.csv does not exist\n";
  }
}

void runExperimentGroup(int jobs, int machines) {
  for (int i = 0; i < 10; ++i) {
    std::string filename =
        "instances/tai" +
        std::to_string(jobs) + "_" +
        std::to_string(machines) + "_" +
        std::to_string(i) +
        ".fsp";

    std::cout << "Running: "
              << filename
              << '\n';

    Instance instance = loadInstance(filename);

    runExperiments(instance, filename);
  }
}