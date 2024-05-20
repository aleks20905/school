#include <iostream>
#include <unordered_map>
#include <chrono>

using namespace std;


int main() {
    auto start = chrono::steady_clock::now();

    unordered_map<double, double> hm;
    double c = 0.0;
    for (int i = 0; i < 10000000; i++) {
        hm[c] = c + 10.0;
        c += 1.0;
    }

    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time : " << duration << " ms" << endl;



// Time : 11729 ms


}
