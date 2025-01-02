#include <iostream>
#include <climits>

using namespace std;

#define MAX_INTERSECTIONS 5

bool isValid(int signalTimings[MAX_INTERSECTIONS], int intersection, int currentTiming, int totalTime) {
    int totalWaitTime = 0;
    for (int i = 0; i < intersection; i++) {
        totalWaitTime += signalTimings[i];
    }

    if (totalWaitTime + currentTiming > totalTime) {
        return false;
    }
    return true;
}

bool optimizeSignalTimingsHelper(int signalTimings[MAX_INTERSECTIONS], int intersection, int totalTime) {
    if (intersection == MAX_INTERSECTIONS) {
        return true;
    }

    for (int currentTiming = 1; currentTiming <= totalTime; currentTiming++) {
        if (isValid(signalTimings, intersection, currentTiming, totalTime)) {
            signalTimings[intersection] = currentTiming;
            if (optimizeSignalTimingsHelper(signalTimings, intersection + 1, totalTime)) {
                return true;
            }
            signalTimings[intersection] = 0;  // Backtrack
        }
    }

    return false;
}

void optimizeSignalTimings(int totalTime) {
    int signalTimings[MAX_INTERSECTIONS] = {0};

    if (optimizeSignalTimingsHelper(signalTimings, 0, totalTime)) {
        cout << "Optimized signal timings for each intersection:" << endl;
        for (int i = 0; i < MAX_INTERSECTIONS; i++) {
            cout << "Intersection " << i + 1 << ": " << signalTimings[i] << " seconds" << endl;
        }
    } else {
        cout << "No valid signal timings found." << endl;
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
    optimizeSignalTimings(totalTime);

    return 0;
}
