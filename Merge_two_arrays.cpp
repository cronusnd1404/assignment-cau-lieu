#include <iostream>
using namespace std;

/*
 * BÀI TOÁN:
 * -----------
 * Cho hai mảng X[] và Y[] đã được sắp xếp tăng dần.
 * Giả sử:
 *    - m = kích thước của X (m >= n)
 *    - n = kích thước của Y
 *    - Trong mảng X có (m-n) phần tử hợp lệ và n ô trống
 * Nhiệm vụ:
 *    - "Nhét" các phần tử của Y vào đúng vị trí trong X
 *      để X vẫn sắp xếp tăng dần sau khi gộp.
 *
 * Ý TƯỞNG CHÍNH:
 * -----------
 * - Ta sẽ duyệt và trộn (merge) từ phía cuối của mảng X.
 * - Dùng 3 chỉ số:
 *     + i: trỏ đến phần tử hợp lệ cuối cùng của X (tức vị trí (m-n-1))
 *     + j: trỏ đến phần tử cuối cùng của Y (tức vị trí (n-1))
 *     + k: trỏ đến vị trí cuối mảng X (vị trí (m-1))
 * - Mỗi bước, so sánh X[i] với Y[j]:
 *     + Nếu X[i] > Y[j], đặt X[k] = X[i], giảm i--.
 *     + Ngược lại, đặt X[k] = Y[j], giảm j--.
 *   Sau đó k-- để tiếp tục "điền" từ cuối mảng lên trên.
 * - Khi một trong hai mảng hết phần tử, nếu Y vẫn còn, 
 *   ta sao chép nốt phần còn lại vào X.
 * - Kết quả thu được X đã sắp xếp hoàn chỉnh.
 */

int main() {
    // 1) Nhập kích thước m, n
    cout << "Nhap kich thuoc m (so phan tu cua X): ";
    int m;
    cin >> m;

    cout << "Nhap kich thuoc n (so phan tu cua Y): ";
    int n;
    cin >> n;

    /*
     * 2) Khai báo mảng X, Y động với kích thước tương ứng.
     *    - X có m ô (trong đó (m-n) ô đã chứa giá trị, n ô trống).
     *    - Y có n ô.
     */
    int* X = new int[m];
    int* Y = new int[n];

    // 3) Nhập (m-n) phần tử đã sắp xếp cho X
    cout << "\nNhap " << (m - n) << " phan tu da sap xep cho X:\n";
    for(int i = 0; i < m - n; i++) {
        cin >> X[i];
    }

    /*
     * Gán n ô trống cuối của X bằng -1 (hay giá trị bất kì),
     * chỉ để minh hoạ đây là ô trống. Thực tế có thể để nguyên hoặc gán 0.
     */
    for(int i = m - n; i < m; i++) {
        X[i] = -1;
    }

    // 4) Nhập n phần tử đã sắp xếp cho Y
    cout << "\nNhap " << n << " phan tu da sap xep cho Y:\n";
    for(int i = 0; i < n; i++) {
        cin >> Y[i];
    }

    /*
     * 5) Tiến hành gộp mảng Y vào X từ phía cuối:
     *    - i: chỉ số cuối của phần tử hợp lệ trong X (m-n-1)
     *    - j: chỉ số cuối của Y (n-1)
     *    - k: chỉ số cuối cùng của X (m-1)
     */
    int i = (m - n) - 1;  // vì (m-n) là số phần tử có giá trị trong X
    int j = n - 1;        // mảng Y có n phần tử, chỉ số cuối là n-1
    int k = m - 1;        // vị trí cuối mảng X

    // So sánh và đặt giá trị lớn hơn về phía cuối của X
    while (i >= 0 && j >= 0) {
        if (X[i] > Y[j]) {
            X[k] = X[i];
            i--;
        } else {
            X[k] = Y[j];
            j--;
        }
        k--;
    }

    /*
     * Nếu còn sót phần tử trong Y (j >= 0) thì chép nốt vào X
     * (vì X đã cạn i, hoặc i < 0).
     * Nếu i vẫn >= 0 thì không cần chép vì chúng đã nằm đúng vị trí.
     */
    while (j >= 0) {
        X[k] = Y[j];
        j--;
        k--;
    }

    // 6) In kết quả: mảng X sau khi gộp
    cout << "\nMang X sau khi gop:\n";
    for(int idx = 0; idx < m; idx++) {
        cout << X[idx] << " ";
    }
    cout << endl;

    // 7) Giải phóng bộ nhớ
    delete[] X;
    delete[] Y;

    return 0;
}
