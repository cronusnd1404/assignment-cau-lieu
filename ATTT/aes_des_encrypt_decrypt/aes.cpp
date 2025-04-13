#include "aes.h"
#include "utils.h"
#include <algorithm> // std::reverse
// AES giả lập: chỉ đảo chuỗi làm ví dụ
void aes_encrypt(const std::string& inputPath, const std::string& outputPath) {
    std::string data = read_file(inputPath);
    std::reverse(data.begin(), data.end()); // mã hóa đơn giản
    write_file(outputPath, data);
}

void aes_decrypt(const std::string& inputPath, const std::string& outputPath) {
    std::string data = read_file(inputPath);
    std::reverse(data.begin(), data.end()); // giải mã = đảo lại
    write_file(outputPath, data);
}
