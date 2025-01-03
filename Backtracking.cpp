#include <iostream>
#include <vector>
using namespace std;

#define MAX_INTERSECTIONS 5

void optimizeSignalTimings(int trafficDensity[MAX_INTERSECTIONS], int totalTime) {
    int totalDensity = 0;
    int signalTimings[MAX_INTERSECTIONS] = {0};

   
    for (int i = 0; i < MAX_INTERSECTIONS; i++) {
        totalDensity += trafficDensity[i];
    }

    
    int remainingTime = totalTime;
    for (int i = 0; i < MAX_INTERSECTIONS; i++) {
        signalTimings[i] = (trafficDensity[i] * totalTime) / totalDensity;
        remainingTime -= signalTimings[i];
    }

    
    for (int i = 0; remainingTime > 0 && i < MAX_INTERSECTIONS; i++) {
        signalTimings[i]++;
        remainingTime--;
    }

    
    cout << "Optimized signal timings for each intersection:" << endl;
    for (int i = 0; i < MAX_INTERSECTIONS; i++) {
        cout << "Intersection " << i + 1 << ": " << signalTimings[i] << " seconds" << endl;
    }
}

int main() {
    int totalTime;

    cout << "Enter the total time available for optimization (in seconds): ";
    cin >> totalTime;

    int trafficDensity[MAX_INTERSECTIONS];
    cout << "Enter the traffic density at each intersection (higher number means more traffic):" << endl;
    for (int i = 0; i < MAX_INTERSECTIONS; i++) {
        cout << "Intersection " << i + 1 << ": ";
        cin >> trafficDensity[i];
    }

    cout << "\nOptimizing signal timings for the intersections..." << endl;
    optimizeSignalTimings(trafficDensity, totalTime);

    return 0;
}
