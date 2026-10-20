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
  bool file_exists = std::ifstream("results.csv").good();
  std::ofstream output("results.csv", std::ios::app);

  if(!output) {
    std::cerr << "Could not create file results.csv\n";
    return;
  }

  if(!file_exists) {
    output << "Distance, n, m, Best Cmax, Standard deviation, NEH Cmax, "
           << "Promedio T CPU, RPD(UB), RPD(NEH)\n";
  }

  //Parameter definition
  unsigned int base_seed = 42;
  int population_size = 50;
  double pc = 0.8;
  double pm = 0.1;
  int tournament_size = 3;

  std::vector<int> cmax_values;
  std::vector<double> cpu_times;

  for (int run = 0; run < 10; ++run) {
    unsigned int seed = base_seed + run;
    GeneticAlgorithm ga(population_size, pc, pm, tournament_size, seed);

    auto start = std::chrono::high_resolution_clock::now();
    ga.run(instance, 50000);

    auto end = std::chrono::high_resolution_clock::now();

    double seconds = std::chrono::duration<double>(end - start).count();

    cmax_values.push_back(ga.getBestMakespan());
    cpu_times.push_back(seconds);
  }

  int best_cmax = *std::min_element(cmax_values.begin(), cmax_values.end());

  double average_cpu = std::accumulate(cpu_times.begin(), cpu_times.end(), 0.0) / cpu_times.size();

  double standard_deviation = calculateStandardDeviation(cmax_values);

  NEH neh;
  neh.run(instance);
  int neh_cmax = neh.getBestMakespan();

  double rpd_ub = calculateRPD(best_cmax, instance.getUpperBound());
  double rpd_neh = calculateRPD(best_cmax, neh_cmax);


  output << instance.getJobs() << ',' << instance.getMachines() << ','
         << best_cmax << ',' << standard_deviation << ',' << neh_cmax << ','
         << average_cpu << ',' << rpd_ub << ',' << rpd_neh << '\n';
}