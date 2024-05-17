#include <iostream>
#include <chrono>

using namespace std;
using ms = chrono::milliseconds;

struct Node {
    Node *next;
    float val;
};

Node *nodes = nullptr;

void iterateAndAdd(double i) {
    Node *node = nodes;
    while (node != nullptr) {
        node->val += i;
        node = node->next;
    }
}

void iterateAndPlace(double val) {
    Node *node = nodes;
    Node *prev = nullptr;

    while (node != nullptr) {
        if (node->val > 99999) {
            break;
        }
        prev = node;
        node = node->next;
    }

    if (prev != nullptr) {
        prev->val = val;
    }
}

int main() {
    Node x = {};
    cout << "Size of struct: " << sizeof(x) << "\n"; // 16 bytes

    for (int i = 0; i < 3000; i++) {
        Node* newNode = new Node;
        newNode->val = 0.0;
        newNode->next = nodes;
        nodes = newNode;
    }

    auto start = chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        iterateAndPlace(100.1);
        iterateAndAdd(i);
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << chrono::duration_cast<ms>(diff).count() << " ms" << endl;

    return 0;
}
