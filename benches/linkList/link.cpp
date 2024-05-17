#include <iostream>
#include <chrono>

using namespace std;
using ms = chrono::milliseconds;

struct Node {
    Node *next;
    float val;
};

Node *nodes = nullptr;

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

    prev->val = val;
}

int main() {
    Node x = {};
    cout << "Size of struct: " << sizeof(x) << "\n"; // 16 bytes

   float initialValue = 0.0;
    for (int i = 0; i < 3000; i++) {
        Node* newNode = new Node;
        newNode->val = initialValue; 
        newNode->next = nodes;
        nodes = newNode;
        initialValue += 1; 
    }

    for (int retrys = 50; retrys < 1000000; retrys+=retrys*0.15) {
    auto start = chrono::steady_clock::now();
    for (int i=0; i<retrys; i++) {
        iterateAndPlace(100.1);
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    // cout <<"size : "<<retrys<<" \t time :  "<< chrono::duration_cast<ms>(diff).count()<<" ms "<<endl;
    cout << chrono::duration_cast<ms>(diff).count()<<endl;

    }
       
    
}       