#include "experiments.h"
#include "genetic_algorithm.h"
#include "instance_reader.h"
#include "metrics.h"
#include "neh.h"
#include "random_search.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


namespace {

  double mean(const std::vector<double>& values) {
    if (values.empty()) { return 0.0; }

    double sum = 0.0;

    for (double value : values) { sum += value; }
    return sum / static_cast<double>(values.size());
  }

  double standardDeviation(const std::vector<double>& values) {
    if (values.empty()) { return 0.0; }

    double average = mean(values);
    double sum = 0.0;

    for (double value : values) {
      double diff = value - average;
      sum += diff * diff;
    }

    return std::sqrt(sum / static_cast<double>(values.size()));
  }

  std::vector<std::string> splitCSV(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream stream(line);
    std::string field;

    while (std::getline(stream,field,',')) {
      fields.push_back(field);
    }
    return fields;
  }


  struct RawResult {
    std::string instance;
    int n;
    int m;
    std::string algorithm;
    int cmax;
    double cpu;
    double rpd;
  };


  struct InstanceStats {
    int n = 0;
    int m = 0;

    std::vector<double> ga_cmax;
    std::vector<double> ga_cpu;
    std::vector<double> ga_rpd;

    int neh_cmax = -1;
  };


}

void runExperiments(const Instance& instance, const std::string& instance_name, int population_size, double pc, double pm, int tournament_size) {

  bool file_exists = std::ifstream("raw_results.csv").good();

  std::ofstream output("raw_results.csv", std::ios::app);

  if (!output) {
    std::cerr << "Could not create raw_results.csv\n";
    return;
  }

  if (!file_exists) {
    output << "Instance,n,m,Algorithm,Run,Seed," << "Population,pc,pm,Tournament," << "Cmax,CPU,RPD(UB)\n";
  }

  unsigned int base_seed = 42;

  // Genetic Algorithm
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
           << "GA" << ',' << run + 1 << ',' << seed << ',' << population_size << ','
           << pc << ',' << pm << ',' << tournament_size << ',' 
           << cmax << ',' << seconds << ',' << rpd_ub << '\n';
  }

  //Random Search
  for (int run = 0; run < 10; ++run) {
    unsigned int seed = base_seed + run;

    RandomSearch random_search(seed);

    auto start = std::chrono::high_resolution_clock::now();

    random_search.run(instance,50000);

    auto end = std::chrono::high_resolution_clock::now();
    double seconds = std::chrono::duration<double>(end - start).count();

    int cmax = random_search.getBestMakespan();

    double rpd_ub = calculateRPD(cmax, instance.getUpperBound());

    output << instance_name << ',' << instance.getJobs() << ',' << instance.getMachines() << ','
           << "RandomSearch" << ',' << run + 1 << ',' << seed << ',' << "-,-,-,-,"
           << cmax << ',' << seconds << ',' << rpd_ub << '\n';
  }

  // NEH (only one run)
  NEH neh;

  auto start = std::chrono::high_resolution_clock::now();

  neh.run(instance);

  auto end = std::chrono::high_resolution_clock::now();
  double seconds = std::chrono::duration<double>(end - start).count();

  int cmax = neh.getBestMakespan();

  double rpd_ub = calculateRPD(cmax, instance.getUpperBound());

  output << instance_name << ',' << instance.getJobs() << ',' << instance.getMachines() << ','
         << "NEH" << ',' << 1 << ',' << "-" << ',' << "-,-,-,-,"
         << cmax << ',' << seconds << ',' << rpd_ub << '\n';
}

void runExperimentGroup(int jobs, int machines, int skip_index) {

  for (int i = 0; i < 10; ++i) {
    if (i == skip_index) { continue; }

    std::string filename = "instances/tai" + std::to_string(jobs) + "_" + std::to_string(machines) + "_" + std::to_string(i) + ".fsp";

    std::cout << "Running: " << filename << '\n';

    Instance instance = loadInstance(filename);

    runExperiments(instance, filename, 50, 0.8, 0.4, 3);
  }
}


void runConvergenceExperiments(const Instance& instance, const std::string& instance_name) {
  std::filesystem::create_directories("results");

  const std::string filename = "results/convergence.csv";

  bool file_exists = std::ifstream(filename).good();

  std::ofstream output(filename, std::ios::app);

  if (!output) {
    std::cerr << "Could not create " << filename << '\n';
    return;
  }

  if (!file_exists) {
    output << "Instance,n,m,Algorithm," << "Run,Seed,Evaluation,BestCmax\n";
  }

  unsigned int base_seed = 42;

  for (int run = 0; run < 10; ++run) {
    unsigned int seed = base_seed + run;

    //Genetic ALgorithm
    GeneticAlgorithm ga(50, 0.8, 0.4, 3,seed);

    ga.run(instance, 50000);

    for (const auto& point : ga.getConvergence()) {

      output << instance_name << ',' << instance.getJobs() << ',' << instance.getMachines() << ',' 
             << "GA" << ',' << run + 1 << ',' << seed << ',' 
             << point.first << ',' << point.second << '\n';
    }

    //Random Search
    RandomSearch random_search(seed);
    random_search.run(instance, 50000);

    for (const auto& point : random_search.getConvergence()) {

      output << instance_name << ',' << instance.getJobs() << ',' << instance.getMachines() << ','
             << "RandomSearch" << ',' << run + 1 << ',' << seed << ',' 
             << point.first << ',' << point.second << '\n';
    }
  }
}


void generateResultTables(const std::string& raw_filename) {

  std::ifstream input(raw_filename);

  if (!input) {
    std::cerr << "Could not open " << raw_filename << '\n';
    return;
  }

  std::filesystem::create_directories("results");
  std::string line;

  //Header
  std::getline(input,line);

  std::vector<RawResult> rows;

  while (std::getline(input, line)) {

    if (line.empty()) { continue; }

    std::vector<std::string> fields = splitCSV(line);

    if (fields.size() < 13) { continue; }

    RawResult row;
    row.instance = fields[0];

    row.n = std::stoi(fields[1]);
    row.m = std::stoi(fields[2]);
    row.algorithm = fields[3];
    row.cmax = std::stoi(fields[10]);
    row.cpu = std::stod( fields[11]);
    row.rpd = std::stod(fields[12]);
    rows.push_back(row);
  }

  std::map<std::string, InstanceStats> instances;

  for (const RawResult& row : rows) {

    InstanceStats& stats = instances[row.instance];
    stats.n = row.n;
    stats.m = row.m;

    if (row.algorithm == "GA") {
      stats.ga_cmax.push_back(row.cmax);
      stats.ga_cpu.push_back(row.cpu);
      stats.ga_rpd.push_back(row.rpd);
    } else if (row.algorithm == "NEH") {
      stats.neh_cmax = row.cmax;
    }
  }

  std::ofstream instance_output("results/instance_summary.csv");

  instance_output << "Instance,n,m," << "BestCmax," << "StdDevCmax," << "NEHCmax,"
                  << "MeanCPU," << "MeanRPD(UB)," << "StdDevRPD(UB)," << "RPD(NEH)\n";

  for (const auto& entry : instances) {

    const std::string& name = entry.first;
    const InstanceStats& stats = entry.second;

    if (stats.ga_cmax.empty()) { continue; }

    double best_cmax = *std::min_element(stats.ga_cmax.begin(), stats.ga_cmax.end());
    double std_cmax = standardDeviation(stats.ga_cmax);
    double mean_cpu = mean(stats.ga_cpu);
    double mean_rpd = mean(stats.ga_rpd);
    double std_rpd = standardDeviation(stats.ga_rpd);

    double rpd_neh = 0.0;

    if (stats.neh_cmax > 0) {
      rpd_neh = 100.0 * (best_cmax - stats.neh_cmax) / stats.neh_cmax;
    }

    instance_output << name << ',' << stats.n << ',' << stats.m << ','
                    << best_cmax << ',' << std_cmax << ',' << stats.neh_cmax << ','
                    << mean_cpu << ',' << mean_rpd << ',' << std_rpd << ',' << rpd_neh << '\n';
  }

 
  // T6 table
  using GroupKey = std::tuple<int, int, std::string>;

  std::map<GroupKey, std::vector<double>> group_rpd;

  for (const RawResult& row : rows) {

    GroupKey key = std::make_tuple(row.n, row.m, row.algorithm);

    group_rpd[key].push_back(row.rpd);
  }

  std::ofstream group_output("results/group_summary.csv");

  group_output << "n,m,Algorithm,MeanRPD(UB)\n";

  for (const auto& entry : group_rpd) {

    int n = std::get<0>(entry.first);
    int m = std::get<1>(entry.first);
    const std::string& algorithm = std::get<2>(entry.first);

    group_output << n << ',' << m << ',' << algorithm << ',' << mean(entry.second) << '\n';
  }

  std::cout << "Created:\n" << "  results/instance_summary.csv\n" << "  results/group_summary.csv\n";
}


void generateConvergenceSummary(const std::string& convergence_filename) {

  std::ifstream input(convergence_filename);

  if (!input) {
    std::cerr << "Could not open " << convergence_filename<< '\n';
    return;
  }

  using Key = std::tuple<std::string, int, int, std::string, int>;

  std::map<Key, std::vector<double>> values;
  std::string line;

  //Header
  std::getline(input, line);

  while (std::getline(input, line)) {

    if (line.empty()) {
      continue;
    }

    auto fields = splitCSV(line);

    if (fields.size() < 8) {
      continue;
    }

    std::string instance = fields[0];

    int n = std::stoi(fields[1]);

    int m = std::stoi(fields[2]);

    std::string algorithm = fields[3];

    int evaluation = std::stoi(fields[6]);

    double best_cmax = std::stod(fields[7]);

    Key key = std::make_tuple(instance, n, m, algorithm, evaluation);

    values[key].push_back(best_cmax);
  }

  std::filesystem::create_directories("results");

  std::ofstream output("results/convergence_summary.csv");

  output << "Instance,n,m,Algorithm," << "Evaluation,MeanBestCmax," << "StdDevBestCmax\n";

  for (const auto& entry : values) {

    const Key& key = entry.first;

    output << std::get<0>(key) << ',' << std::get<1>(key) << ',' << std::get<2>(key) << ',' << std::get<3>(key) << ',' << std::get<4>(key) << ',' << mean(entry.second) << ',' << standardDeviation( entry.second) << '\n';
  }

  std::cout << "Created " << "results/convergence_summary.csv\n";
}


void resetRawResults() {
  if (std::filesystem::remove("raw_results.csv")) {
    std::cout << "raw_results.csv reset successfully\n";
  } else {
    std::cout << "raw_results.csv does not exist\n";
  }
}