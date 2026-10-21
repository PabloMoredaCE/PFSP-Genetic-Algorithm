#ifndef INSTANCE_READER_H_
#define INSTANCE_READER_H_

#include "instance.h"

#include <string>

/**
 * @brief Read a PFSP instance from a file
 * 
 * @param filename Name of the file
 *
 */
Instance loadInstance(const std::string& filename);

#endif