#include "metrics.h"

#include <cmath>

double calculateRPD(int makespan, int upper_bound) {
  if (upper_bound <= 0) { return -1.0; }

  return 100.0 * (makespan - upper_bound) / upper_bound;
}

double calculateRPDNEH(int makespan, int neh_makespan) {
  return 100.0 * (makespan - neh_makespan) / neh_makespan;
}

double calculateStandardDeviation(const std::vector<int>& values) {
  double mean = 0.0;

  for (int value : values) { mean += value;}
  mean /= values.size();

  double sum = 0.0;
  for (int value : values) {
    double difference = value - mean;
    sum += difference * difference;
  }

  return std::sqrt(sum / values.size());
}