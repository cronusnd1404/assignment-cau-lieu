#ifndef DES_H
#define DES_H

#include <string>

void des_encrypt(const std::string& inputPath, const std::string& outputPath);
void des_decrypt(const std::string& inputPath, const std::string& outputPath);

#endif
