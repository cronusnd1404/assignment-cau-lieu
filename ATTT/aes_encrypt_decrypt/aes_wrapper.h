#ifndef AES_WRAPPER_H
#define AES_WRAPPER_H

#include <string>
#include <cstdint>

void encryptAES(const std::string& inputFile, const std::string& outputFile, const uint8_t key[16]);
void decryptAES(const std::string& inputFile, const std::string& outputFile, const uint8_t key[16]);

#endif
