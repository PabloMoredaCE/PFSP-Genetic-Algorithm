#include "metrics.h"

double Metrics::calculateRPD(int makespan, int upper_bound) {
  if (upper_bound <= 0) { return -1.0; }

  return 100.0 * (makespan - upper_bound) / upper_bound;
}