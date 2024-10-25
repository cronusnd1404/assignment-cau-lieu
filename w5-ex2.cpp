#include <stdio.h>
#include <math.h>

c
// Ham kiem tra so nguyen to
int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Ham kiem tra so Blum
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

// Tao mang so Blum nho hon N
int generate_blum_numbers(int blum_numbers[], int N) {
    int count = 0;
    for (int i = 6; i < N; i++) {
        if (is_blum_number(i)) {
            blum_numbers[count++] = i;
        }
    }
    return count;
}

// Tim cap so Blum co tong cung la so Blum
void find_blum_pairs(int blum_numbers[], int count, int N) {
    printf("Cac cap so Blum co tong cung la so Blum: ");
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
        printf("Khong co cap nao.\n");
    } else {
        printf("\n");
    }
}

// Kiem tra su ton tai cua so Blum M trong day
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
    printf("Mang so Blum nho hon %d: ", N);
    for (int i = 0; i < count; i++) {
        printf("%d ", blum_numbers[i]);
    }
    printf("\n");
    int M = 33;
    if (check_blum_existence(M, blum_numbers, count)) {
        printf("So Blum %d ton tai trong mang.\n", M);
    } else {
        printf("So Blum %d khong ton tai trong mang.\n", M);
    }
    find_blum_pairs(blum_numbers, count, N);
    return 0;
}