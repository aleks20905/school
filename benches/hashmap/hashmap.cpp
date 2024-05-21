#include <iostream>
#include <unordered_map>
#include <chrono>
#include <fstream>
#include <sstream>
#include <unistd.h>

using namespace std;


void printMemoryUsage() { //са мо за Linix 
    ifstream file("/proc/self/statm");
    if (!file.is_open()) {
        cerr << "Error: Could not open /proc/self/statm" << endl;
        return;
    }
    long size, resident, share, text, lib, data, dt;
    file >> size >> resident >> share >> text >> lib >> data >> dt;
    file.close();

    long pageSize = sysconf(_SC_PAGESIZE); // In bytes 
    long residentSize = resident * pageSize;

    cout << "Memory Usage: " << residentSize / 1024 << " KB" << endl; // Convert to KB
}

int main() {
    
    unordered_map<double, double> hm;
    printMemoryUsage();
    // Memory Usage: 3328 KB
    
    auto start = chrono::steady_clock::now();
    
    for (int i = 0; i < 10000000; i++) {
        hm[i] = i + 10.0;
    }

    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "create Time : " << duration << " ms" << endl;
    printMemoryUsage();

// Time : 7697 ms
// Memory Usage: 410560 KB

    start = chrono::steady_clock::now();
    
    for (int i = 0; i < 10000000; i++) {
        hm[i] = hm[i] + i ;
    }

    end = chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "modify Time : " << duration << " ms" << endl;
    printMemoryUsage();

// Time : 4697 ms
// Memory Usage: 410560 KB

}
