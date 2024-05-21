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

int main() {
    Node x = {};
    cout << "Size of struct: " << sizeof(x) << "\n";

    float initialValue = 0.0;
    for (int i = 0; i < 3000; i++) {
        Node* newNode = new Node;
        newNode->val = initialValue;
        newNode->next = nodes;
        nodes = newNode;
        initialValue += 1.0;
    }

    
    for (int retrys = 50; retrys < 1000000; retrys += retrys * 0.15) {
        auto start = chrono::steady_clock::now();
        clock_t cpu_start = clock();
        for (int i = 0; i < retrys; i++) {
            iterateAndPlace(100.1);
        }
        clock_t cpu_end = clock();
        auto end = chrono::steady_clock::now();
        auto diff = end - start;

        double wall_clock_time = chrono::duration_cast<ms>(diff).count();
        double cpu_time = 1000.0 * (cpu_end - cpu_start) / CLOCKS_PER_SEC;
        double cpu_utilization = (cpu_time / wall_clock_time) * 100.0;

        cout << "Time: " << setw(7) << wall_clock_time << " ms | ";
        cout << "CPU Time: " <<setw(9) << cpu_time << " ms | ";
        cout << "Memory Usage: " << setw(9) << getMemoryUsage() << " bytes | ";
        cout << "CPU Utilization: " << setw(8) << cpu_utilization << " %" << endl;
    }


    return 0;
}
