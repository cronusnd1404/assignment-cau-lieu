#include <iostream>
#include <string>

struct Node {
    std::string word; // Luu tu trong cau
    int count;        // Dem so lan xuat hien cua tu
    Node* next;

    Node(const std::string& word) : word(word), count(1), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Them tu vao danh sach neu tu chua co neu co roi thi tang bien dem
    void addWord(const std::string& word) {
        Node* existingNode = findWord(word);
        if (existingNode) {
            existingNode->count++;
        } else {
            Node* newNode = new Node(word);
            newNode->next = head;
            head = newNode;
        }
    }

    // Tim tu trong danh sach tra ve node neu tim thay
    Node* findWord(const std::string& word) {
        Node* current = head;
        while (current) {
            if (current->word == word) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Xac dinh tu xuat hien nhieu nhat
    std::string findMostFrequentWord() {
        if (!head) return "";
        Node* current = head;
        Node* mostFrequent = head;
        while (current) {
            if (current->count > mostFrequent->count) {
                mostFrequent = current;
            }
            current = current->next;
        }
        return mostFrequent->word;
    }

    // Loai bo tu lay vi du xanh xanh
    void removeRepeatedWords() {
        Node* current = head;
        while (current && current->next) {
            if (current->word == current->next->word) {
                Node* duplicate = current->next;
                current->next = duplicate->next;
                delete duplicate;
            } else {
                current = current->next;
            }
        }
    }

    // Dem so tu vung khac nhau trong cau
    int countUniqueWords() {
        int count = 0;
        Node* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    // Hien thi danh sach cac tu va tan suat cua chung
    void displayWords() {
        Node* current = head;
        while (current) {
            std::cout << "Word: " << current->word << ", Count: " << current->count << std::endl;
            current = current->next;
        }
    }

    // Giai phong bo nho
    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList sentence;

    // Them cac tu vao cau
    sentence.addWord("xanh");
    sentence.addWord("xanh");
    sentence.addWord("xanh");
    sentence.addWord("dep");
    sentence.addWord("dep");
    sentence.addWord("tuoi");

    std::cout << "Danh sach cac tu trong cau:\n";
    sentence.displayWords();

    // Tim tu xuat hien nhieu nhat
    std::string mostFrequentWord = sentence.findMostFrequentWord();
    std::cout << "Tu xuat hien nhieu nhat: " << mostFrequentWord << std::endl;

    // Loai bo tu lay
    sentence.removeRepeatedWords();
    std::cout << "\nSau khi loai bo tu lay:\n";
    sentence.displayWords();

    // Dem so tu vung khac nhau
    int uniqueWordCount = sentence.countUniqueWords();
    std::cout << "\nSo tu vung khac nhau: " << uniqueWordCount << std::endl;

    return 0;
}
