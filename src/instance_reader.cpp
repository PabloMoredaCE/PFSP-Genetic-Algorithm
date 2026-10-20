#include "instance_reader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

Instance loadInstance(const std::string& filename) {
  std::ifstream input{filename};

  if (!input) {
    throw std::runtime_error("Could not open file: " + filename);
  }

  int jobs;
  int machines;
  int upper_bound = -1;

  std::string first_line;
  std::getline(input, first_line);

  std::istringstream first_stream(first_line);

  // Simple format
  if (first_stream >> jobs >> machines) {
    upper_bound = -1;
  } else {
    // Taillard format
    std::string data_line;
    std::getline(input, data_line);

    std::istringstream data_stream(data_line);

    int initial_seed;
    int lower_bound;
    if (!(data_stream >> jobs >> machines >> initial_seed
                      >> upper_bound >> lower_bound)) {
      throw std::runtime_error("Invalid header in: " + filename);
    }

    // Skip header line
    std::string processing_header;
    std::getline(input, processing_header);
  }

  std::vector<std::vector<int>> processing_times(machines, std::vector<int>(jobs));
  for (int machine = 0; machine < machines; ++machine) {
    for (int job = 0; job < jobs; ++job) {
      if (!(input >> processing_times[machine][job])) {
        throw std::runtime_error("Invalid processing times in: " + filename);
      }
    }
  }

  return Instance(jobs, machines, processing_times, upper_bound);
}