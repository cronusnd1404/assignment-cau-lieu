#include <iostream>
using namespace std;

struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[9];
    char hoTen[50];
    int gioiTinh;  // 0: Nam, 1: Nu
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien data;
    Node* link;
};

struct List {
    Node* first;
    Node* last;
};

// Khoi tao danh sach
void khoiTaoList(List &l) {
    l.first = nullptr;
    l.last = nullptr;
}

// Tao mot sinh vien moi
Node* taoNode(SinhVien sv) {
    Node* newNode = new Node;
    newNode->data = sv;
    newNode->link = nullptr;
    return newNode;
}

int soSanhChuoi(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        i++;
    }
    return s1[i] - s2[i];
}

// Ham so sanh ngay
bool soSanhNgay(Ngay ngay1, Ngay ngay2) {
    return ngay1.ngay == ngay2.ngay && ngay1.thang == ngay2.thang && ngay1.nam == ngay2.nam;
}

// Them sinh vien vao danh sach theo thu tu ma sinh vien
void themSinhVien(List &l, SinhVien sv) {
    Node* newNode = taoNode(sv);
    if (l.first == nullptr || soSanhChuoi(l.first->data.maSV, sv.maSV) > 0) {
        newNode->link = l.first;
        l.first = newNode;
        if (l.last == nullptr) {
            l.last = newNode;
        }
    } else {
        Node* current = l.first;
        while (current->link != nullptr && soSanhChuoi(current->link->data.maSV, sv.maSV) < 0) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
        if (newNode->link == nullptr) {
            l.last = newNode;
        }
    }
}

// Ham in thong tin sinh vien
void inThongTinSV(SinhVien sv) {
    cout << "Ma SV: " << sv.maSV << ", Ho Ten: " << sv.hoTen << ", Gioi Tinh: " << (sv.gioiTinh == 1 ? "Nu" : "Nam")
         << ", Ngay Sinh: " << sv.ngaySinh.ngay << "/" << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam
         << ", Dia Chi: " << sv.diaChi << ", Lop: " << sv.lop << ", Khoa: " << sv.khoa << endl;
}

// Ham in danh sach sinh vien
void inDanhSach(List l) {
    Node* current = l.first;
    while (current != nullptr) {
        inThongTinSV(current->data);
        current = current->link;
    }
}

// Ham hoan đoi du lieu cua hai sinh vien
void hoanDoiSinhVien(SinhVien &a, SinhVien &b) {
    SinhVien temp = a;
    a = b;
    b = temp;
}

// Ham sap xep danh sach sinh vien theo ma sinh vien
void sapXepListSV(List &l) {
    if (l.first == nullptr) return;  // Kiểm tra danh sách trống

    for (Node* i = l.first; i != nullptr; i = i->link) {
        for (Node* j = i->link; j != nullptr; j = j->link) {
            if (soSanhChuoi(i->data.maSV, j->data.maSV) > 0) {
                hoanDoiSinhVien(i->data, j->data);  // Hoán đổi dữ liệu của hai sinh viên
            }
        }
    }
}

// Ham in cac sinh vien co cung ngay sinh
void inSinhVienCungNgaySinh(List l) {
    bool found = false;
    for (Node* i = l.first; i != nullptr; i = i->link) {
        bool hasDuplicate = false;
        for (Node* j = i->link; j != nullptr; j = j->link) {
            if (soSanhNgay(i->data.ngaySinh, j->data.ngaySinh)) {
                if (!hasDuplicate) {
                    cout << "Cac sinh vien co ngay sinh " << i->data.ngaySinh.ngay << "/"
                         << i->data.ngaySinh.thang << "/" << i->data.ngaySinh.nam << " la:" << endl;
                    inThongTinSV(i->data);
                    hasDuplicate = true;
                    found = true;
                }
                inThongTinSV(j->data);
            }
        }
    }
    if (!found) {
        cout << "Khong tim thay sinh vien co cung ngay sinh." << endl;
    }
}

// Ham xoa sinh vien co cung ngay sinh
void xoaSinhVienCungNgaySinh(List &l) {
    Node* current = l.first;
    Node* prev = nullptr;

    while (current != nullptr) {
        bool hasDuplicate = false;
        Node* checker = current->link;

        while (checker != nullptr) {
            if (soSanhNgay(current->data.ngaySinh, checker->data.ngaySinh)) {
                hasDuplicate = true;
                break;
            }
            checker = checker->link;
        }

        if (hasDuplicate) {
            if (prev == nullptr) {
                l.first = current->link;
            } else {
                prev->link = current->link;
            }

            Node* temp = current;
            current = current->link;
            delete temp;
        } else {
            prev = current;
            current = current->link;
        }
    }
    l.last = prev;  // Cập nhật l.last sau khi xóa
}

int main() {
    List l;
    khoiTaoList(l);

    SinhVien sv1 = { "20224442", "Ta Nguyen Long", 0, {15, 5, 2004}, "Phu Tho", "IoT", "K67" };
    SinhVien sv2 = { "20224433", "Tran Thi Thu", 1, {20, 9, 2004}, "Ha Noi", "CNTT", "K67" };
    SinhVien sv3 = { "20224446", "Nguyen Van Hung", 0, {15, 5, 2004}, "Nam Dinh", "KHMT", "K67" };
    SinhVien sv4 = { "20214441", "Le Minh Hieu", 0, {22, 11, 2003}, "Hai Phong", "IoT", "K66" };
    SinhVien sv5 = { "20224440", "Do Thi Mai", 1, {10, 2, 2004}, "Hai Duong", "KTMT", "K67" };
    SinhVien sv6 = { "20234444", "Pham Duc Anh", 0, {12, 6, 2005}, "Ha Noi", "KHMT", "K68" };
    SinhVien sv7 = { "20224453", "Bui Van Quang", 0, {15, 5, 2004}, "Ha Nam", "VT", "K67" };
    SinhVien sv8 = { "20234455", "Nguyen Thi Bich", 1, {1, 1, 2005}, "Bac Ninh", "CNTT", "K68" };
    SinhVien sv9 = { "20214450", "Hoang Tuan Kiet", 0, {1, 1, 2003}, "Da Nang", "IoT", "K66" };
    SinhVien sv10 = { "20224451", "Nguyen Tien Dung", 0, {25, 12, 2004}, "Quang Ninh", "CNTT", "K67" };

    themSinhVien(l, sv1);
    themSinhVien(l, sv2);
    themSinhVien(l, sv3);
    themSinhVien(l, sv4);
    themSinhVien(l, sv5);
    themSinhVien(l, sv6);
    themSinhVien(l, sv7);
    themSinhVien(l, sv8);
    themSinhVien(l, sv9);
    themSinhVien(l, sv10);

    cout << "Danh sach sinh vien:" << endl;
    inDanhSach(l);

    cout << "\nCac sinh vien co cung ngay sinh:" << endl;
    inSinhVienCungNgaySinh(l);

    cout << "\nDanh sach sinh vien sau khi xoa sinh vien co cung ngay sinh:" << endl;
    xoaSinhVienCungNgaySinh(l);
    inDanhSach(l);

    return 0;
}
