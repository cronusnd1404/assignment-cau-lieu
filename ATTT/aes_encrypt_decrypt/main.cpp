#include "aes_wrapper.h"

int main() {
    const uint8_t key[16] = {
        'm', 'y', 's', 'e', 'c', 'r', 'e', 't',
        'k', 'e', 'y', '1', '2', '3', '4', '5'
    };

    encryptAES("input.txt", "encrypted.txt", key);
    decryptAES("encrypted.txt", "decrypted.txt", key);

    return 0;
}
// Chuyển đổi file input.txt thành file encrypted.txt bằng AES với key đã cho