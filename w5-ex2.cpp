#include <stdio.h>
#include <math.h>

// Hàm kiểm tra số nguyên tố
int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Hàm kiểm tra số Blum
int is_blum_number(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0 && is_prime(i) && (i % 4 == 3)) {
            int complement = n / i;
            if (is_prime(complement) && (complement % 4 == 3)) {
                return 1;
            }
        }
    }
    return 0;
}

// Tạo mảng số Blum nhỏ hơn N
int generate_blum_numbers(int blum_numbers[], int N) {
    int count = 0;
    for (int i = 6; i < N; i++) {
        if (is_blum_number(i)) {
            blum_numbers[count++] = i;
        }
    }
    return count;
}

// Tìm cặp số Blum có tổng cũng là số Blum
void find_blum_pairs(int blum_numbers[], int count, int N) {
    printf("Các cặp số Blum có tổng cũng là số Blum: ");
    int found = 0;
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            int sum = blum_numbers[i] + blum_numbers[j];
            if (sum < N && is_blum_number(sum)) {
                printf("(%d, %d) ", blum_numbers[i], blum_numbers[j]);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("Không có cặp nào.\n");
    } else {
        printf("\n");
    }
}

// Kiểm tra sự tồn tại của số Blum M trong dãy
int check_blum_existence(int M, int blum_numbers[], int count) {
    for (int i = 0; i < count; i++) {
        if (blum_numbers[i] == M) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int N = 100;
    int blum_numbers[100];
    int count = generate_blum_numbers(blum_numbers, N);
    printf("Mảng số Blum nhỏ hơn %d: ", N);
    for (int i = 0; i < count; i++) {
        printf("%d ", blum_numbers[i]);
    }
    printf("\n");
    int M = 33;
    if (check_blum_existence(M, blum_numbers, count)) {
        printf("Số Blum %d tồn tại trong mảng.\n", M);
    } else {
        printf("Số Blum %d không tồn tại trong mảng.\n", M);
    }
    find_blum_pairs(blum_numbers, count, N);
    return 0;
}