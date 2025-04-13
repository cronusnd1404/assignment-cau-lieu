#include "des.h"
#include "utils.h"

void des_encrypt(const std::string& inputPath, const std::string& outputPath) {
    std::string data = read_file(inputPath);
    for (char &c : data) c += 1; // mã hóa đơn giản
    write_file(outputPath, data);
}

void des_decrypt(const std::string& inputPath, const std::string& outputPath) {
    std::string data = read_file(inputPath);
    for (char &c : data) c -= 1;
    write_file(outputPath, data);
}
