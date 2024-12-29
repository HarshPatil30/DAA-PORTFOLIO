#include <iostream>
#include <climits>

using namespace std;

#define MAX_INTERSECTIONS 5

void deploySensors(int trafficDensity[MAX_INTERSECTIONS], int n) {
    int maxTraffic = INT_MIN;
    int intersection = -1;

    for (int i = 0; i < n; i++) {
        if (trafficDensity[i] > maxTraffic) {
            maxTraffic = trafficDensity[i];
            intersection = i;
        }
    }

    if (intersection != -1) {
        cout << "Deploy traffic sensor at intersection " << intersection << " with traffic density: " << maxTraffic << endl;
    } else {
        cout << "No intersections to monitor." << endl;
    }
}

int main() {
    int trafficDensity[MAX_INTERSECTIONS] = {25, 60, 35, 80, 45}; 

    deploySensors(trafficDensity, MAX_INTERSECTIONS);

    return 0;
}
