#include <iostream>
using namespace std;

#define MAX_INTERSECTIONS 5

// Intersection names
string intersectionNames[MAX_INTERSECTIONS] = {
    "City Center", "Restaurant", "Park", "Hospital", "Highway"
};


void merge(int arr[], int left, int mid, int right, int intersections[]) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];
    int leftIntersections[n1], rightIntersections[n2];

  
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
        leftIntersections[i] = intersections[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
        rightIntersections[i] = intersections[mid + 1 + i];
    }

    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            intersections[k] = leftIntersections[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            intersections[k] = rightIntersections[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        intersections[k] = leftIntersections[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        intersections[k] = rightIntersections[j];
        j++;
        k++;
    }
}


void mergeSort(int arr[], int left, int right, int intersections[]) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, intersections);
        mergeSort(arr, mid + 1, right, intersections);

        merge(arr, left, mid, right, intersections);
    }
}


void displayGreenLightTimes(int congestionLevels[], int intersections[], int size, int totalGreenTime) {
    cout << "Green light timings for each intersection based on congestion levels:" << endl;

    
    int totalCongestion = 0;
    for (int i = 0; i < size; i++) {
        totalCongestion += congestionLevels[i];
    }

    for (int i = 0; i < size; i++) {
        
        int greenTime = (congestionLevels[i] * totalGreenTime) / totalCongestion;
        cout << intersectionNames[intersections[i]] << ": " << greenTime << " seconds" << endl;
    }
}

int main() {
    int congestionLevels[MAX_INTERSECTIONS];  
    int intersections[MAX_INTERSECTIONS] = {0, 1, 2, 3, 4};  

    cout << "Enter the traffic congestion levels for " << MAX_INTERSECTIONS << " intersections:" << endl;
    for (int i = 0; i < MAX_INTERSECTIONS; i++) {
        cout << intersectionNames[i] << ": ";
        cin >> congestionLevels[i];  
    }

    
    mergeSort(congestionLevels, 0, MAX_INTERSECTIONS - 1, intersections);

    int totalGreenTime;
    cout << "\nEnter the total green light time available (in seconds): ";
    cin >> totalGreenTime;

    
    displayGreenLightTimes(congestionLevels, intersections, MAX_INTERSECTIONS, totalGreenTime);

    return 0;
}
