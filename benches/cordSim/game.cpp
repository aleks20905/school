#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Player {
private:
    int x, y, z;

public:

    Player(int initialX = 0, int initialY = 0, int initialZ = 0)
        : x(initialX), y(initialY), z(initialZ) {}

    void moveTo(int newX, int newY, int newZ) {
        x = newX;
        y = newY;
        z = newZ;
        //cout << "Player moved to position (" << x << ", " << y << ", " << z << ")\n";
    }

    void moveFromFile(const string& filename) {
        ifstream infile(filename);
        if (infile.is_open()) {
            int newX, newY, newZ;
            infile >> newX >> newY >> newZ;
            if (!infile.fail()) {
                moveTo(newX, newY, newZ);
            } else {
                cerr << "Error: Invalid data in file\n";
            }
            infile.close();
        } else {
            cerr << "Error: Could not open file\n";
        }
    }
};

int main() {
    Player player;

    string filename = "position.txt";
    player.moveFromFile(filename);

    return 0;
}
