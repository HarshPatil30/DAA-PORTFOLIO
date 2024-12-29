#include <iostream>
using namespace std;

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

void locateCongestionPatterns(int arr[], int size, int target) {
    int result = binarySearch(arr, 0, size - 1, target);
    
    if (result != -1) {
        cout << "Congestion point " << target << " found at index " << result << endl;
    } else {
        cout << "Congestion point " << target << " not found." << endl;
    }
}

int main() {
    int congestionLevels[] = {10, 20, 20, 30, 40, 40, 50, 60, 70, 80}; // Sorted traffic congestion levels
    int size = sizeof(congestionLevels) / sizeof(congestionLevels[0]);

    int targetCongestion = 40; // Example: Searching for the congestion level of 40 units

    locateCongestionPatterns(congestionLevels, size, targetCongestion);

    return 0;
}
