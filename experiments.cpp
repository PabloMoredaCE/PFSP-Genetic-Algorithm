#include "experiments.h"
#include "genetic_algorithm.h"
#include "metrics.h"
#include "neh.h"

#include <fstream>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <numeric>

void runExperiments(const Instance& instance, const std::string& instance_name) {
  bool file_exists = std::ifstream("raw_results.csv").good();
  std::ofstream output("raw_results.csv", std::ios::app);

  if(!output) {
    std::cerr << "Could not create file raw_results.csv\n";
    return;
  }

  if(!file_exists) {
    output << "Instance,n,m,Algorithm,Run,Seed, "
           << "Cmax,CPU,RPD(UB)\n";
  }

  //Parameter definition
  unsigned int base_seed = 42;
  int population_size = 50;
  double pc = 0.8;
  double pm = 0.1;
  int tournament_size = 3;


  for (int run = 0; run < 10; ++run) {
    unsigned int seed = base_seed + run;
    GeneticAlgorithm ga(population_size, pc, pm, tournament_size, seed);

    auto start = std::chrono::high_resolution_clock::now();
    ga.run(instance, 50000);

    auto end = std::chrono::high_resolution_clock::now();

    double seconds = std::chrono::duration<double>(end - start).count();

    int cmax = ga.getBestMakespan();

    double rpd_ub = calculateRPD(cmax, instance.getUpperBound());

     output << instance_name << instance.getJobs() << ',' << instance.getMachines() << ','
         << "GA" << ',' << run + 1 << ',' << seed << ','
         << cmax << ',' << seconds << ',' << rpd_ub << '\n';
  }
}