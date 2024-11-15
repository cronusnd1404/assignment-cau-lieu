#include <iostream>
#include <stack>
#include <string>
using namespace std;

// dinh nghia thanh go
struct Wood {
    string type;  
    double size;
    int age;      

    // Constructor cho struct Wood
    Wood(string t, double s, int a) : type(t), size(s), age(a) {}
};

// Ham dem so luong thanh go co cung tuoi trong stack
int countWoodsByAge(stack<Wood> woodStack, int age) {
    int count = 0;

    // Duyet qua tung thanh go trong stack
    while (!woodStack.empty()) {
        Wood wood = woodStack.top();  // Lay thanh go o dinh stack
        woodStack.pop();               // Xoa thanh go khoi stack tam thoi

        if (wood.age == age) {
            count++;
        }
    }
    return count;
}

int main() {
    stack<Wood> woodStack;

    // Them mot so thanh go vao stack
    woodStack.push(Wood("Oak", 2.5, 5));
    woodStack.push(Wood("Pine", 1.8, 3));
    woodStack.push(Wood("Maple", 3.2, 5));
    woodStack.push(Wood("Cedar", 2.0, 7));
    woodStack.push(Wood("Walnut", 2.7, 5));

    // Nhap tuoi can dem
    int ageToCount;
    cout << "Nhap tuoi can dem: ";
    cin >> ageToCount;

    // Dem so luong thanh go co tuoi bang ageToCount
    int result = countWoodsByAge(woodStack, ageToCount);
    cout << "So luong thanh go co tuoi " << ageToCount << " la: " << result << endl;

    return 0;
}
