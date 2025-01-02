#include <iostream>
using namespace std;

// Binary Search function to locate the congestion level
int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if the target is at mid
        if (arr[mid] == target) {
            return mid;
        }

        // If target is smaller, ignore right half
        if (arr[mid] > target) {
            right = mid - 1;
        }
        // If target is larger, ignore left half
        else {
            left = mid + 1;
        }
    }

    // Target not found
    return -1;
}

// Function to locate the congestion patterns based on the user input
void locateCongestionPatterns(int arr[], int size, int target) {
    int result = binarySearch(arr, 0, size - 1, target);
    
    if (result != -1) {
        cout << "Congestion point " << target << " found at index " << result << endl;
    } else {
        cout << "Congestion point " << target << " not found." << endl;
    }
}

int main() {
    int size;
    cout << "Enter the number of intersections (areas): ";
    cin >> size;

    int congestionLevels[size];

    cout << "Enter the congestion levels at each intersection (sorted order preferred, higher number means more congestion):" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Intersection " << i + 1 << ": ";
        cin >> congestionLevels[i];
    }

    int targetCongestion;
    cout << "\nEnter the congestion level to search for: ";
    cin >> targetCongestion;

    locateCongestionPatterns(congestionLevels, size, targetCongestion);

    return 0;
}
