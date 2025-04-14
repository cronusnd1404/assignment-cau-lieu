#include "aes_wrapper.h"
#include "aes.h"
#include <fstream>
#include <vector>

const int BLOCK_SIZE = 16;

void readFile(const std::string& filename, std::vector<uint8_t>& data) {
    std::ifstream file(filename, std::ios::binary);
    data.assign(std::istreambuf_iterator<char>(file), {});
}

void writeFile(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

void pad(std::vector<uint8_t>& data) {
    size_t pad_len = BLOCK_SIZE - (data.size() % BLOCK_SIZE);
    data.insert(data.end(), pad_len, static_cast<uint8_t>(pad_len));
}

void unpad(std::vector<uint8_t>& data) {
    if (!data.empty()) {
        uint8_t pad = data.back();
        data.resize(data.size() - pad);
    }
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

    writeFile(outputFile, data);
}

void decryptAES(const std::string& inputFile, const std::string& outputFile, const uint8_t key[16]) {
    std::vector<uint8_t> data;
    readFile(inputFile, data);

    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);

    for (size_t i = 0; i < data.size(); i += BLOCK_SIZE) {
        AES_ECB_decrypt(&ctx, &data[i]);
    }

    unpad(data);
    writeFile(outputFile, data);
}
