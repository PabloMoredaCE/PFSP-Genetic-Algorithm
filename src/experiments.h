#ifndef EXPERIMENTS_H_
#define EXPERIMENTS_H_

#include "instance.h"

#include <string>

/**
 * @brief Executes the experimental comparison on a single PFSP instance.
 *
 * Runs the Genetic Algorithm and the reference algorithms, storing the
 * obtained results in the raw results file.
 *
 * The Genetic Algorithm parameters can be configured through the function
 * arguments.
 *
 * @param instance PFSP instance to evaluate.
 * @param instance_name Name or path used to identify the instance.
 * @param population_size Genetic Algorithm population size.
 * @param pc Crossover probability.
 * @param pm Mutation probability.
 * @param tournament_size Tournament size used during selection.
 */
void runExperiments(const Instance& instance, const std::string& instance_name,
      int population_size = 50, double pc = 0.8, double pm = 0.4, int tournament_size = 3);

/**
 * @brief Removes the current raw experimental results.
 *
 * Used before starting a new set of experiments in order to avoid mixing
 * previous results with the new executions.
 */
void resetRawResults();

/**
 * @brief Executes experiments for a complete instance group.
 *
 * Loads and evaluates the instances belonging to the specified n x m group.
 * An instance index can optionally be skipped, for example when that instance
 * was previously used during parameter tuning.
 *
 * @param jobs Number of jobs of the instance group.
 * @param machines Number of machines of the instance group.
 * @param skip_index Index of the instance to skip.
 *        A value of -1 means that no instance is skipped.
 */
void runExperimentGroup(int jobs, int machines, int skip_index = -1);

/**
 * @brief Executes experiments used to analyze algorithm convergence.
 *
 * Records the evolution of the best makespan found as the number of
 * evaluations increases.
 *
 * @param instance PFSP instance to evaluate.
 * @param instance_name Name or path used to identify the instance.
 */
void runConvergenceExperiments(const Instance& instance, const std::string& instance_name);

/**
 * @brief Generates summary tables from the raw experimental results.
 *
 * Processes the raw CSV file and produces aggregated result tables for
 * individual instances and instance groups.
 *
 * @param raw_filename Path to the raw results CSV file.
 */
void generateResultTables(const std::string& raw_filename);

/**
 * @brief Generates an aggregated convergence summary.
 *
 * Reads the raw convergence data and calculates summary statistics for each
 * evaluation checkpoint.
 *
 * @param convergence_filename Path to the convergence CSV file.
 */
void generateConvergenceSummary(const std::string& convergence_filename);

#endif