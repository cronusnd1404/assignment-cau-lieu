#include <stdio.h>

void dutch_national_flag_sort(int arr[], int n) {
    int low = 0, mid = 0, high = n - 1;
    while (mid <= high) {
        switch (arr[mid]) {
            case 0: // Mau do
                arr[low] = arr[low] + arr[mid] - (arr[mid] = arr[low]);
                low++;
                mid++;
                break;
            case 1: // Mau trang
                mid++;
                break;
            case 2: // Mau xanh
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
    int colors[] = {1,2,0,0,1,2,0,0,1,2,0,0};
    int n = sizeof(colors) / sizeof(colors[0]);
    dutch_national_flag_sort(colors, n);
    printf("Mang sau khi sap xep: ");
    print_array(colors, n);
    return 0;
}