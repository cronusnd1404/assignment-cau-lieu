#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;

    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

double evaluate(Node* root){
    if (!root) return 0;

    if (!root->left && !root->right) {
        try {
            return stod(root->value);
        } catch (invalid_argument&) {
            throw runtime_error("Variable not supported in evaluation");
        }
    }

    double left_val = evaluate(root->left);
    double right_val = evaluate(root->right);

    if (root->value == "+") {
        return left_val + right_val;
    } else if (root->value == "-") {
        return left_val - right_val;
    } else if (root->value == "*") {
        return left_val * right_val;
    } else if (root->value == "/") {
        if (right_val == 0) throw runtime_error("Error: Division by zero");
        return left_val / right_val;
    } else if (root->value == "^") {
        return pow(left_val, right_val);
    }
}

Node* buildExpressionTree() {
    Node* root = new Node("+");

    root->left = new Node("-");
    root->left->left = new Node("+");
    root->left->left->left = new Node("a");
    root->left->left->right = new Node("*");
    root->left->left->right->left = new Node("5");
    root->left->left->right->right = new Node("b");
    root->left->right = new Node("^");
    root->left->right->left = new Node("c");
    root->left->right->right = new Node("8");

    root->right = new Node("*");
    root->right->left = new Node("d");
    root->right->right = new Node("^");
    root->right->right->left = new Node("e");
    root->right->right->right = new Node("0.5");

    return root;
}

int main() {
    try {
        Node* root = buildExpressionTree();
        double result = evaluate(root);
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
