#ifndef AES_H
#define AES_H

#include <string>

void aes_encrypt(const std::string& inputPath, const std::string& outputPath);
void aes_decrypt(const std::string& inputPath, const std::string& outputPath);

#endif
