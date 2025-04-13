#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string read_file(const std::string& path);
void write_file(const std::string& path, const std::string& data);

#endif
