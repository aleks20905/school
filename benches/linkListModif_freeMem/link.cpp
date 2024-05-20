#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <iomanip>


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
size_t getMemoryUsage() {
    ifstream file("/proc/self/statm");
    if (!file.is_open()) {
        cerr << "Error: Could not open /proc/self/statm" << endl;
        return 0;
    }
    long size, resident, share, text, lib, data, dt;
    file >> size >> resident >> share >> text >> lib >> data >> dt;
    file.close();

    long pageSize = sysconf(_SC_PAGESIZE); // In bytes 
    long residentSize = resident * pageSize;

    return residentSize;
}
void calNode(int n ){
    
    for (int i = 0; i < n; i++) {
        Node* newNode = new Node;
        newNode->val = 0.0;
        newNode->next = nodes;
        nodes = newNode;
    }

    auto start = chrono::steady_clock::now();
    for (int i = 0; i < 10000; i++) {
        iterateAndPlace(100.1);
        iterateAndAdd(i);
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout <<"node N: "<<n<<" "<< chrono::duration_cast<ms>(diff).count() << " ms" << " mem usage: "<<getMemoryUsage()<< endl;

    // Free the allocated memory
    Node* current = nodes;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    nodes = nullptr; // reset

}


int main() {
    Node x = {};
    cout << "Size of struct: " << sizeof(x) << "\n"; // 16 bytes

    for (int i = 200; i < 10000; i+=200)
    {
        calNode(i);

    }
    
    

    return 0;
}
