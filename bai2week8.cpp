#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Ham nhap da thuc
vector<pair<int, int>> inputPolynomial() {
    vector<pair<int, int>> polynomial;
    int n;
    cout << "Nhap so hang tu cua da thuc: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int coeff, power;
        cout << "Nhap he so: ";
        cin >> coeff;
        cout << "Nhap bac: ";
        cin >> power;
        polynomial.push_back({coeff, power});
    }
    return polynomial;
}

// Ham cong hai da thuc
vector<pair<int, int>> addPolynomials(const vector<pair<int, int>>& poly1, const vector<pair<int, int>>& poly2) {
    vector<pair<int, int>> result;
    // Tao mot ban sao cua cac da thuc de thuc hien phep cong
    auto temp = poly1;

    // Duyet qua tung hang tu cua poly2 va them vao poly1
    for (const auto& term : poly2) {
        bool found = false;
        for (auto& t : temp) {
            if (t.second == term.second) {
                t.first += term.first;
                found = true;
                break;
            }
        }
        if (!found) {
            temp.push_back(term);
        }
    }

    // Loc bo cac hang tu co he so bang 0 va sap xep theo bac giam dan
    for (const auto& t : temp) {
        if (t.first != 0) {
            result.push_back(t);
        }
    }
    sort(result.begin(), result.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    });
    return result;
}

// Ham in da thuc
void printPolynomial(const vector<pair<int, int>>& poly) {
    for (size_t i = 0; i < poly.size(); ++i) {
        int coeff = poly[i].first;
        int power = poly[i].second;

        if (i > 0 && coeff > 0) cout << " + ";
        if (coeff < 0) cout << " - ";

        cout << abs(coeff);
        if (power > 0) cout << ".x";
        if (power > 1) cout << "^" << power;
    }
    cout << endl;
}

// Ham chinh
int main() {
    cout << "Nhap da thuc f(x):" << endl;
    vector<pair<int, int>> f = inputPolynomial();

    cout << "\nNhap da thuc g(x):" << endl;
    vector<pair<int, int>> g = inputPolynomial();

    cout << "\nDa thuc f(x) = ";
    printPolynomial(f);

    cout << "\nDa thuc g(x) = ";
    printPolynomial(g);

    vector<pair<int, int>> h = addPolynomials(f, g);
    cout << "\nTong cua hai da thuc h(x) = f(x) + g(x) la: ";
    printPolynomial(h);

    return 0;
}
