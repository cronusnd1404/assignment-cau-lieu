#include "aes_wrapper.h"
#include "aes.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

const int BLOCK_SIZE = 16;

// Đọc file nhị phân vào vector byte
void readFile(const std::string& filename, std::vector<uint8_t>& data) {
    std::ifstream file(filename, std::ios::binary);
    data.assign(std::istreambuf_iterator<char>(file), {});
}

// Ghi vector byte ra file nhị phân
void writeFile(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

// Padding dữ liệu theo block 16 byte
void pad(std::vector<uint8_t>& data) {
    size_t pad_len = BLOCK_SIZE - (data.size() % BLOCK_SIZE);
    data.insert(data.end(), pad_len, static_cast<uint8_t>(pad_len));
}

// Gỡ padding sau khi giải mã
void unpad(std::vector<uint8_t>& data) {
    if (!data.empty()) {
        uint8_t pad = data.back();
        if (pad <= BLOCK_SIZE)
            data.resize(data.size() - pad);
    }
}

// Chuyển vector byte sang chuỗi hex
std::string bytesToHex(const std::vector<uint8_t>& data) {
    std::ostringstream oss;
    for (uint8_t byte : data) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    return oss.str();
}

// Chuyển chuỗi hex thành vector byte
std::vector<uint8_t> hexToBytes(const std::string& hex) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = (uint8_t) strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

void encryptAES(const std::string& inputFile, const std::string& outputFile, const uint8_t key[16]) {
    std::vector<uint8_t> data;
    readFile(inputFile, data);
    pad(data);

    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);

    for (size_t i = 0; i < data.size(); i += BLOCK_SIZE) {
        AES_ECB_encrypt(&ctx, &data[i]);
    }

    std::string hexData = bytesToHex(data);
    std::ofstream outFile(outputFile);
    outFile << hexData;
}

void decryptAES(const std::string& inputFile, const std::string& outputFile, const uint8_t key[16]) {
    std::ifstream inFile(inputFile);
    std::string hexData((std::istreambuf_iterator<char>(inFile)), {});
    std::vector<uint8_t> data = hexToBytes(hexData);

    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);

    for (size_t i = 0; i < data.size(); i += BLOCK_SIZE) {
        AES_ECB_decrypt(&ctx, &data[i]);
    }

    unpad(data);
    writeFile(outputFile, data);
}
// Chuyển đổi file encrypted.txt thành file decrypted.txt bằng AES với key đã cho