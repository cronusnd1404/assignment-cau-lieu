#include <iostream>
using namespace std;

struct AVLNode {
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

int getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

int getBalanceFactor(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void updateHeight(AVLNode* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

AVLNode* balance(AVLNode* node) {
    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);

    // Left-heavy case
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left); // Left-Right case
        }
        return rotateRight(node); // Left-Left case
    }

    // Right-heavy case
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right); // Right-Left case
        }
        return rotateLeft(node); // Right-Right case
    }

    return node; // Balanced
}

AVLNode* insert(AVLNode* node, int key) {
    if (!node) {
        return new AVLNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    return balance(node);
}

void printInOrder(AVLNode* root) {
    if (root) {
        printInOrder(root->left);
        cout << root->key << " ";
        printInOrder(root->right);
    }
}

void printPreOrder(AVLNode* root) {
    if (root) {
        cout << root->key << " ";
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

int main() {
    AVLNode* root = nullptr;
    int keys[] = {10, 20, 30, 40,60, 50, 25};

    cout << "Insertion steps with AVL tree balancing:\n";
    for (int key : keys) {
        root = insert(root, key);
        cout << "After inserting " << key << ":\n";
        cout << "InOrder: ";
        printInOrder(root);
        cout << "\nPreOrder: ";
        printPreOrder(root);
        cout << "\n\n";
    }

    return 0;
}
