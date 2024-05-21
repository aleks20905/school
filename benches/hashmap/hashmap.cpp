#include <iostream>
#include <unordered_map>
#include <chrono>

using namespace std;


int main() {
    
    unordered_map<double, double> hm;
    
    auto start = chrono::steady_clock::now();
    
    for (int i = 0; i < 10000000; i++) {
        hm[i] = i + 10.0;
    }

    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "create Time : " << duration << " ms" << endl;

// Time : 7697 ms

    start = chrono::steady_clock::now();
    
    for (int i = 0; i < 10000000; i++) {
        hm[i] = hm[i] + i ;
    }

    end = chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "modify Time : " << duration << " ms" << endl;

// Time : 4697 ms

}
