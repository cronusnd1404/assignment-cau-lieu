#include "aes.h"
#include "des.h"

int main() {
    // AES
    aes_encrypt("input.txt", "aes_output.txt");
    aes_decrypt("aes_output.txt", "aes_decrypted.txt");

    // DES
    des_encrypt("input.txt", "des_output.txt");
    des_decrypt("des_output.txt", "des_decrypted.txt");

    return 0;
}
