#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class RC4 {
private:
    vector<unsigned char> S;
    int i, j;

    void KSA(const vector<unsigned char>& key) {
        for (int k = 0; k < 256; k++)
            S[k] = k;

        int j = 0;
        for (int k = 0; k < 256; k++) {
            j = (j + S[k] + key[k % key.size()]) % 256;
            swap(S[k], S[j]);
        }
    }

    unsigned char PRGA() {
        i = (i + 1) % 256;
        j = (j + S[i]) & 0xFF;
        swap(S[i], S[j]);
        return S[(S[i] + S[j]) % 256];
    }

public:
    RC4(const vector<unsigned char>& key) : S(256), i(0), j(0) {
        KSA(key);
    }

    vector<unsigned char> encrypt(const vector<unsigned char>& data) {
        vector<unsigned char> output;
        for (unsigned char c : data)
            output.push_back(c ^ PRGA());
        return output;
    }

    vector<unsigned char> generate_keystream(size_t length) {
        vector<unsigned char> keystream;
        for (size_t k = 0; k < length; k++)
            keystream.push_back(PRGA());
        return keystream;
    }
};

void print_hex(const vector<unsigned char>& data, const string& label) {
    cout << label << ": ";
    for (unsigned char c : data)
        cout << hex << setw(2) << setfill('0') << (int)c << " ";
    cout << endl;
}

int main() {
    string key_str;
    string plaintext;

    cout << "Nhap khoa mat khau: ";
    getline(cin, key_str);
    cout << "Nhap van ban can ma hoa: ";
    getline(cin, plaintext);

    vector<unsigned char> key(key_str.begin(), key_str.end());
    vector<unsigned char> data(plaintext.begin(), plaintext.end());

    RC4 rc4(key);
    vector<unsigned char> keystream = rc4.generate_keystream(data.size());
    vector<unsigned char> ciphertext = rc4.encrypt(data);

    print_hex(keystream, "Keystream");
    print_hex(ciphertext, "Ciphertext");

    return 0;
}

/* demo output
Nhap khoa mat khau: bimat
Nhap van ban can ma hoa: Hanoi University of Science and Technology 
Keystream: 19 6a 0c 0c b5 9a 25 30 e2 fa 48 ee 9c bc 8f 54 1e 9e 0e 96 78 6b cb 08 ef 98 8b 70 8b cc a8 66 e0 36 d3 58 a7 8d 9b 75 2a 4c 
Ciphertext: b2 b0 a0 f9 f6 e1 47 80 f3 22 15 e4 37 22 34 63 76 6f ff c8 52 55 14 e5 ca 6d aa f2 98 d7 c4 27 b8 d3 62 fe ab 7a 9d c6 c9 a1  */