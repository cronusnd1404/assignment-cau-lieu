#include <iostream>
#include <string>

struct File {
    std::string name;
    double size;           // Kich thuoc file (MB)
    int timestamp;         // Thoi gian luu (timestamp)
    File* next;            // Con tro toi file tiep theo

    File(const std::string& name, double size, int timestamp)
        : name(name), size(size), timestamp(timestamp), next(nullptr) {}
};

class FileList {
private:
    File* head;

public:
    FileList() : head(nullptr) {}

    // Them file vao danh sach
    void addFile(const std::string& name, double size, int timestamp) {
        File* newFile = new File(name, size, timestamp);
        if (!head) {
            head = newFile;
        } else {
            File* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newFile;
        }
    }

    // Sap xep danh sach theo dung luong tang dan
    void sortBySize() {
        if (!head || !head->next) return;

        File* current;
        File* index;
        double tempSize;
        int tempTimestamp;
        std::string tempName;

        for (current = head; current != nullptr; current = current->next) {
            for (index = current->next; index != nullptr; index = index->next) {
                if (current->size > index->size || (current->size == index->size && current->timestamp > index->timestamp))// Hoan doi thong tin file 
                {
                    tempSize = current->size;
                    current->size = index->size;
                    index->size = tempSize;

                    tempTimestamp = current->timestamp;
                    current->timestamp = index->timestamp;
                    index->timestamp = tempTimestamp;

                    tempName = current->name;
                    current->name = index->name;
                    index->name = tempName;
                }
            }
        }
    }

    // Xoa file o dau danh sach
    void deleteAtHead() {
        if (!head) return;

        File* temp = head;
        head = head->next;
        delete temp;
    }

    // Xoa file o cuoi danh sach
    void deleteAtTail() {
        if (!head) return;

        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }

        File* current = head;
        while (current->next && current->next->next) {
            current = current->next;
        }

        delete current->next;
        current->next = nullptr;
    }

    // Xoa file sau mot node cho truoc
    void deleteAfter(File* prev) {
        if (!prev || !prev->next) return;

        File* temp = prev->next;
        prev->next = temp->next;
        delete temp;
    }

    // Xoa file co dung luong be nhat va thoi gian luu lau nhat
    void deleteMinFile() {
        if (!head) return;

        sortBySize(); // Dam bao danh sach da duoc sap xep

        // Xoa file o dau danh sach (file be nhat va luu lau nhat)
        deleteAtHead();
    }

    // Hien thi danh sach file
    void displayFiles() {
        File* current = head;
        while (current) {
            std::cout << "File: " << current->name
                      << ", Size: " << current->size << " MB"
                      << ", Timestamp: " << current->timestamp << std::endl;
            current = current->next;
        }
    }

    // Giai phong bo nho
    ~FileList() {
        while (head) {
            File* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    FileList files;

    // Them file vao danh sach
    files.addFile("File1.txt", 1.5, 1620012345);
    files.addFile("File2.txt", 2.0, 1620010000);
    files.addFile("File3.txt", 1.5, 1610000000);
    files.addFile("File4.txt", 3.0, 1620015678);

    std::cout << "Danh sach file truoc khi sap xep:\n";
    files.displayFiles();

    // Sap xep danh sach theo dung luong va thoi gian
    files.sortBySize();
    std::cout << "\nDanh sach file sau khi sap xep:\n";
    files.displayFiles();

    // Xoa file co dung luong nho nhat va thoi gian luu lau nhat
    files.deleteMinFile();
    std::cout << "\nDanh sach file sau khi xoa file nho nhat va luu lau nhat:\n";
    files.displayFiles();

    return 0;
}
