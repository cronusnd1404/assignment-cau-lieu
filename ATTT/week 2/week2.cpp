#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int SIZE = 5;

// Tạo bảng mã hóa từ khóa
vector<vector<char>> generateKeyMatrix(string key) {
    vector<vector<char>> matrix(SIZE, vector<char>(SIZE));
    map<char, bool> used;
    key += "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Bỏ qua 'J'
    int row = 0, col = 0;

    for (char c : key) {
        if (c == 'J') c = 'I'; // Thay 'J' bằng 'I'
        if (!used[c]) {
            matrix[row][col] = c;
            used[c] = true;
            col++;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
    return matrix;
}

// Tìm vị trí của ký tự trong bảng mã hóa
pair<int, int> findPosition(char c, vector<vector<char>>& matrix) {
    if (c == 'J') c = 'I'; // Thay thế 'J' bằng 'I'
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

// Xử lý chuỗi bản rõ thành các cặp ký tự
vector<pair<char, char>> processPlaintext(string text) {
    vector<pair<char, char>> pairs;
    string processedText = "";
    
    for (char c : text) {
        if (c != ' ') processedText += toupper(c);
    }

    for (size_t i = 0; i < processedText.size(); i++) {
        if (processedText[i] == 'J') processedText[i] = 'I';
        if (i + 1 < processedText.size() && processedText[i] == processedText[i + 1]) {
            pairs.push_back({processedText[i], 'X'});
        } else if (i + 1 < processedText.size()) {
            pairs.push_back({processedText[i], processedText[i + 1]});
            i++;
        } else {
            pairs.push_back({processedText[i], 'X'});
        }
    }
    return pairs;
}

// Mã hóa Playfair
string encrypt(string plaintext, string key) {
    vector<vector<char>> keyMatrix = generateKeyMatrix(key);
    vector<pair<char, char>> pairs = processPlaintext(plaintext);
    string ciphertext = "";

    for (auto [a, b] : pairs) {
        auto [row1, col1] = findPosition(a, keyMatrix);
        auto [row2, col2] = findPosition(b, keyMatrix);

        if (row1 == row2) {
            ciphertext += keyMatrix[row1][(col1 + 1) % SIZE];
            ciphertext += keyMatrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext += keyMatrix[(row1 + 1) % SIZE][col1];
            ciphertext += keyMatrix[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext += keyMatrix[row1][col2];
            ciphertext += keyMatrix[row2][col1];
        }
    }
    return ciphertext;
}

int main() {
    string plaintext, key;
    cout << "Nhap ban ro: ";
    getline(cin, plaintext);
    cout << "Nhap khoa: ";
    getline(cin, key);

    string ciphertext = encrypt(plaintext, key);
    cout << "Ban ma: " << ciphertext << endl;
    return 0;
}

//OUTPUT
/* Nhap ban ro: TOIYEUBACHKHOA
Nhap khoa: IOTNHUNG
Ban ma: NTNVDGCBLCLNTG */