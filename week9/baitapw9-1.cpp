#include <iostream>
#include <string>

using namespace std;
struct File {
    std::string name;        // Ten file
    double size;             // Kich thuoc file (tinh bang GB)
    time_t creationTime;     // Thoi gian tao file

    File(std::string name, double size, time_t creationTime)
        : name(name), size(size), creationTime(creationTime) {}
};

struct Node {
    File file;
    Node* next;

    Node(File file) : file(file), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList() : head(nullptr) {}

    // Chen mot file vao danh sach theo thu tu thoi gian
    void insertFile(File newFile) {
        Node* newNode = new Node(newFile);
        if (!head || head->file.creationTime >= newFile.creationTime) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->file.creationTime < newFile.creationTime) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Tinh tong kich thuoc cua tat ca cac file trong thu muc
    double calculateTotalSize() {
        double totalSize = 0.0;
        Node* current = head;
        while (current) {
            totalSize += current->file.size;
            current = current->next;
        }
        return totalSize;
    }

    // Sao luu cac file vao USB voi kich thuoc toi da 32GB
    void backupToUSB() {
        const double USB_MAX_SIZE = 32.0;
        while (calculateTotalSize() > USB_MAX_SIZE) {
            removeSmallestFile();
        }
    }

    // Xoa file co kich thuoc nho nhat de tiet kiem dung luong
    void removeSmallestFile() {
        if (!head) return;
        Node *smallest = head, *current = head, *prevSmallest = nullptr, *prev = nullptr;

        while (current) {
            if (current->file.size < smallest->file.size) {
                smallest = current;
                prevSmallest = prev;
            }
            prev = current;
            current = current->next;
        }

        if (smallest == head) {
            head = head->next;
        } else if (prevSmallest) {
            prevSmallest->next = smallest->next;
        }
        delete smallest;
    }

    // Hien thi cac file trong thu muc
    void displayFiles() {
        Node* current = head;
        while (current) {
            std::cout << "File: " << current->file.name << ", Size: " << current->file.size
                      << "GB, Created at: " << ctime(&(current->file.creationTime));
            current = current->next;
        }
    }
};



int main() {
    LinkedList documentList;

    // Gia lap them file vao thu muc
    documentList.insertFile(File("File1.txt", 1.5, time(0) - 10000));   // Tao file 1.5GB
    documentList.insertFile(File("File2.txt", 5.0, time(0) - 5000));    // Tao file 5GB
    documentList.insertFile(File("File3.txt", 10.0, time(0) - 2000));   // Tao file 10GB
    documentList.insertFile(File("File4.txt", 20.0, time(0)));          // Tao file 20GB

    cout << "Cac file trong thu muc D>Document:\n";
    documentList.displayFiles();

    cout << "\nTong kich thuoc thu muc: " << documentList.calculateTotalSize() << "GB\n";

    // Sao luu cac file vao USB
    documentList.backupToUSB();
    cout << "\nSau khi sao luu, danh sach file trong thu muc:\n";
    documentList.displayFiles();

    return 0;
}
