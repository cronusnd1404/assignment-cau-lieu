#include <iostream>
#include <string>

using namespace std;

struct Node {
    string title;
    int pages;
    Node* children[100];
    int childCount;

    Node(string t, int p) : title(t), pages(p), childCount(0) {}
};

Node* createBook() {
    Node* root = new Node("Book Title", 0);

    Node* chapter1 = new Node("Chapter 1", 30);
    Node* chapter2 = new Node("Chapter 2", 40);

    Node* section1 = new Node("Section 1.1", 10);
    Node* section2 = new Node("Section 1.2", 20);
    Node* subsection1 = new Node("Subsection 1.2.1", 10);

    section2->children[section2->childCount++] = subsection1;
    chapter1->children[chapter1->childCount++] = section1;
    chapter1->children[chapter1->childCount++] = section2;

    root->children[root->childCount++] = chapter1;
    root->children[root->childCount++] = chapter2;

    return root;
}

int countChapters(Node* root) {
    if (!root) return 0;

    int count = 0;
    for (int i = 0; i < root->childCount; ++i) {
        if (root->children[i]->title.find("Chapter") != string::npos) {
            count++;
        }
    }
    return count;
}

Node* findLongestChapter(Node* root) {
    if (!root) return nullptr;

    Node* longestChapter = nullptr;
    int maxPages = 0;

    for (int i = 0; i < root->childCount; ++i) {
        if (root->children[i]->title.find("Chapter") != string::npos && root->children[i]->pages > maxPages) {
            maxPages = root->children[i]->pages;
            longestChapter = root->children[i];
        }
    }

    return longestChapter;
}

void deleteNode(Node* root, const string& titleToDelete) {
    if (!root) return;

    for (int i = 0; i < root->childCount; ++i) {
        if (root->children[i]->title == titleToDelete) {
            delete root->children[i];
            for (int j = i; j < root->childCount - 1; ++j) {
                root->children[j] = root->children[j + 1];
            }
            root->childCount--;
            return;
        }
    }

    for (int i = 0; i < root->childCount; ++i) {
        deleteNode(root->children[i], titleToDelete);
    }
}

void printBook(Node* root, int level = 0) {
    if (!root) return;

    for (int i = 0; i < level; ++i) cout << "  ";
    cout << root->title << " (" << root->pages << " pages)\n";

    for (int i = 0; i < root->childCount; ++i) {
        printBook(root->children[i], level + 1);
    }
}

int main() {
    Node* book = createBook();

    cout << "Number of chapters: " << countChapters(book) << endl;

    Node* longestChapter = findLongestChapter(book);
    if (longestChapter) {
        cout << "Longest chapter: " << longestChapter->title << " (" << longestChapter->pages << " pages)\n";
    }

    cout << "Book before deletion:\n";
    printBook(book);

    deleteNode(book, "Section 1.2");

    cout << "Book after deletion:\n";
    printBook(book);

    return 0;
}
