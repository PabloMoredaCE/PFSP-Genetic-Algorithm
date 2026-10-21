#ifndef METRICS_H_
#define METRICS_H_

#include <vector>

    /**
     * @brief Calculates the Relative Percentage Deviation (RPD).
     *
     * RPD measures the quality of a solution with respect to a known upper bound.
     * A lower value indicates a better solution.
     *
     * @param makespan Makespan obtained by the algorithm.
     * @param upper_bound Known upper bound used as reference.
     * @return Relative Percentage Deviation in percentage.
     */
    double calculateRPD(int makespan, int upper_bound);

    /**
     * @brief Calculates the standard deviation of a set of integer values.
     *
     * @param values Vector containing the values to analyze.
     * @return Standard deviation of the values.
     */
    double calculateStandardDeviation(const std::vector<int>& values);

#endif
