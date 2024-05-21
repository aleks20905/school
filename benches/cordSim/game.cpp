#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <unistd.h>

using namespace std;

struct Coordinate {
    double x;
    double y;
    double z;
};

class Player {
    Coordinate position;
public:
    

    Player() : position{0, 0, 0} {}

    vector<Coordinate> MoveTo(const vector<Coordinate>& coordinates) {
        if (coordinates.size() < 2) {
            cerr << "Error: Not enough coordinates to determine direction" << endl;
            return {};
        }

        vector<Coordinate> directions;
        Coordinate prevCoord = coordinates[0];

        for (const auto& currCoord : coordinates) {
            double dx = currCoord.x - prevCoord.x; //нарочно да е малко по бавно 
            double dy = currCoord.y - prevCoord.y;
            double dz = currCoord.z - prevCoord.z;
            directions.push_back({dx, dy, dz});
            prevCoord = currCoord;
        }
        return directions;
    }

    vector<Coordinate> MoveToOffset(const vector<Coordinate>& coordinates, double offset) {
        if (coordinates.size() < 2) {
            cerr << "Error: Not enough coordinates to determine direction" << endl;
            return {};
        }

        vector<Coordinate> directions;
        Coordinate prevCoord = coordinates[0];

        for (const auto& currCoord : coordinates) {
            double dx = currCoord.x - prevCoord.x + offset;
            double dy = currCoord.y - prevCoord.y + offset;
            double dz = currCoord.z - prevCoord.z + offset;
            directions.push_back({dx, dy, dz});
            prevCoord = currCoord;
        }
        return directions;
    }

    double CalculateDistanceFromDirections(const vector<Coordinate>& directions) {
        if (directions.empty()) {
            cerr << "Error: Not enough directions to determine distance traveled" << endl;
            return 0;
        }

        double totalDistance = 0.0;
        for (const auto& d : directions) {
            double distance = sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
            totalDistance += distance;
        }
        return totalDistance;
    }
};

vector<Coordinate> ReadAndParseFile() {
    ifstream file("position.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open file";
    }

    vector<Coordinate> coordinates;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        double x, y, z;
        if (!(iss >> x >> y >> z)) {
            cerr << "Error: Invalid data in file";
        }
        coordinates.push_back({x, y, z});
    }
    return coordinates;
}

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
    vector<Coordinate> coordinates;
    coordinates = ReadAndParseFile();
   

    auto start = chrono::steady_clock::now();

    for (int i = 0; i < 100; ++i) {
        Player player;

        vector<Coordinate> directions = player.MoveTo(coordinates);
        double distanceTraveled = player.CalculateDistanceFromDirections(directions);
        //cout << "Distance Traveled: " << distanceTraveled << endl;

        directions = player.MoveToOffset(coordinates, static_cast<double>(i));
        distanceTraveled = player.CalculateDistanceFromDirections(directions);
        //cout << "Distance Traveled: " << distanceTraveled << endl;
    }

    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time taken: " << duration << " ms" << endl;

    printMemoryUsage();    

// Time taken: 20056 ms
// Memory Usage: 27020 KB

    return 0;
}
