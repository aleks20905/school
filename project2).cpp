#include <iostream>

using namespace std;

bool underLine(double x1, double y1, double x2, double y2) {
    return (y1 < -x1 + 1) && (y2 < -x2 + 1);
}

int maxConnections(double x[], double y[], int size) {
    int maxCount = 0;

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {

            if (underLine(x[i], y[i], x[j], y[j])) {
                maxCount++;
            }
        }
    }
    return maxCount;
}

int main() {
    double x[24] = {3,1.5,-3,-4,2.5,12,-3.5,-2.5,-1.5,-2.5,3.5,1.5,0.5,-5,6,-4,0,-5.5,-1,-2,4,-1,-5,-4.5};
    double y[24] = {8.5,5,2.5,4,3.5,3,6.5,-8.5,-10,-8,1.5,1,1.5,-4.5,-2.5,1,-1,0.5,3,-0.5,-1,1,1.5,2};
    int size = sizeof(x) / sizeof(x[0]); // Calculate the size of the arrays

    int maxConn = maxConnections(x, y, size);
    cout << "maximum connections under y = -x + 1  is: " << maxConn << endl;

    return 0;
}