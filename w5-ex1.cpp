#include <stdio.h>

void dutch_national_flag_sort(int arr[], int n) {
    int low = 0, mid = 0, high = n - 1;
    while (mid <= high) {
        switch (arr[mid]) {
            case 0: // Màu đỏ
                arr[low] = arr[low] + arr[mid] - (arr[mid] = arr[low]);
                low++;
                mid++;
                break;
            case 1: // Màu trắng
                mid++;
                break;
            case 2: // Màu xanh
                arr[high] = arr[high] + arr[mid] - (arr[mid] = arr[high]);
                high--;
                break;
        }
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int colors[] = {2, 0, 2, 0, 0, 1, 0, 2, 1};
    int n = sizeof(colors) / sizeof(colors[0]);
    dutch_national_flag_sort(colors, n);
    printf("Mảng sau khi sắp xếp: ");
    print_array(colors, n);
    return 0;
}