#include <iostream>
using namespace std;

struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;  // 0: Nữ, 1: Nam
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

// Khởi tạo danh sách
void khoiTaoList(List &l) {
    l.first = nullptr;
    l.last = nullptr;
}

// Tạo một sinh viên mới
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

// Thêm sinh viên vào danh sách theo thứ tự mã sinh viên
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

// Hàm in thông tin sinh viên
void inThongTinSV(SinhVien sv) {
    cout << "Ma SV: " << sv.maSV << ", Ho Ten: " << sv.hoTen << ", Gioi Tinh: " << (sv.gioiTinh == 1 ? "Nam" : "Nu")
         << ", Ngay Sinh: " << sv.ngaySinh.ngay << "/" << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam
         << ", Dia Chi: " << sv.diaChi << ", Lop: " << sv.lop << ", Khoa: " << sv.khoa << endl;
}

// Hàm in danh sách sinh viên
void inDanhSach(List l) {
    Node* current = l.first;
    while (current != nullptr) {
        inThongTinSV(current->data);
        current = current->link;
    }
}

// Hàm in các sinh viên có cùng ngày sinh
void inSinhVienCungNgaySinh(List l) {
    bool found = false;
    for (Node* i = l.first; i != nullptr; i = i->link) {
        bool hasDuplicate = false;
        for (Node* j = i->link; j != nullptr; j = j->link) {
            if (i->data.ngaySinh.ngay == j->data.ngaySinh.ngay &&
                i->data.ngaySinh.thang == j->data.ngaySinh.thang &&
                i->data.ngaySinh.nam == j->data.ngaySinh.nam) {
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

// Giải phóng bộ nhớ của danh sách
void giaiPhongDanhSach(List &l) {
    while (l.first != nullptr) {
        Node* temp = l.first;
        l.first = l.first->link;
        delete temp;
    }
    l.last = nullptr;
}

int main() {
    List l;
    khoiTaoList(l);

    // Tạo dữ liệu mẫu
    SinhVien sv1 = { "123", "Nguyen Van A", 1, {15, 5, 2002}, "Ha Noi", "CNTT", "K65" };
    SinhVien sv2 = { "124", "Tran Thi B", 0, {15, 5, 2002}, "Ha Noi", "KHMT", "K65" };
    SinhVien sv3 = { "122", "Le Van C", 1, {12, 12, 2001}, "Hai Phong", "VT", "K64" };

    // Thêm sinh viên vào danh sách
    themSinhVien(l, sv1);
    themSinhVien(l, sv2);
    themSinhVien(l, sv3);

    // In danh sách sinh viên
    cout << "Danh sach sinh vien:" << endl;
    inDanhSach(l);

    // In các sinh viên có cùng ngày sinh
    cout << "\nCac sinh vien co cung ngay sinh:" << endl;
    inSinhVienCungNgaySinh(l);

    // Giải phóng bộ nhớ
    giaiPhongDanhSach(l);

    return 0;
}
