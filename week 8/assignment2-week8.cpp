#include <iostream>
using namespace std;

// Cau truc cho moi nguoi choi
struct Node {
    int data;
    Node* next;
};

// Ham tao danh sach vong tron lien ket voi N nguoi
Node* createCircularList(int N) {
    Node* head = new Node{1, nullptr};
    Node* prev = head;
    for (int i = 2; i <= N; i++) {
        Node* newNode = new Node{i, nullptr};
        prev->next = newNode;
        prev = newNode;
    }
    prev->next = head; // Ket noi nut cuoi voi nut dau de tao thanh vong tron
    return head;
}

// Ham tim nguoi chien thang theo luat Josephus
int josephus(int N, int M) {
    Node* head = createCircularList(N);

    // Chi con mot nguoi thi do la nguoi chien thang
    while (head->next != head) {
        // Di chuyen M-1 buoc de tim nguoi bi loai
        for (int i = 1; i < M; i++) {
            head = head->next;
        }
        // Xoa nguoi choi tai vi tri head->next
        Node* temp = head->next;
        head->next = temp->next;
        cout << "Nguoi choi bi loai: " << temp->data << endl;
        delete temp;

        // Di chuyen den nguoi tiep theo
        head = head->next;
    }

    // Nguoi chien thang cuoi cung
    int winner = head->data;
    delete head;
    return winner;
}

int main() {
    int N, M;
    cout << "Nhap so nguoi choi (N): ";
    cin >> N;
    cout << "Nhap so buoc M: ";
    cin >> M;

    int winner = josephus(N, M);
    cout << "Nguoi chien thang la: " << winner << endl;

    return 0;
}
