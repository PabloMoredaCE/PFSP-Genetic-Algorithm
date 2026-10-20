#ifndef EXPERIMENTS_H_
#define EXPERIMENTS_H_

#include "instance.h"

#include <string>

void runExperiments(const Instance& instance, const std::string& instance_name,
      int population_size = 50, double pc = 0.8, double pm = 0.4, int tournament_size = 3);

void resetRawResults();

void runExperimentGroup(int jobs, int machines);

#endif