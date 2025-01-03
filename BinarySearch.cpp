#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
using namespace std;

#define MAX_INTERSECTIONS 5

// Binary Search function to locate the congestion level
int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if the target is at mid
        if (arr[mid] == target) {
            return mid;
        }

        // If target is smaller, ignore the right half
        if (arr[mid] > target) {
            right = mid - 1;
        }
        // If target is larger, ignore the left half
        else {
            left = mid + 1;
        }
    }

    // Target not found
    return -1;
}

// Function to locate the congestion level based on the intersection number
void locateCongestionLevel(int arr[], int idx[], int size, int target) {
    if (target >= 1 && target <= size) {
        int intersectionIndex = target - 1;  // Convert to 0-based index
        cout << "Congestion level at Intersection " << target << " is " << arr[intersectionIndex] << " congestion units." << endl;
    } else {
        cout << "Invalid intersection number!" << endl;
    }
}

void merge(int arr[], int left, int mid, int right, int idx[]) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2], leftIdx[n1], rightIdx[n2];

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
        leftIdx[i] = idx[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
        rightIdx[i] = idx[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] >= rightArr[j]) { // Sort in descending order
            arr[k] = leftArr[i];
            idx[k] = leftIdx[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            idx[k] = rightIdx[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        idx[k] = leftIdx[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        idx[k] = rightIdx[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right, int idx[]) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, idx);
        mergeSort(arr, mid + 1, right, idx);

        merge(arr, left, mid, right, idx);
    }
}

void displayCongestionLevels(int arr[], int idx[], int size) {
    cout << "Congestion levels sorted from highest to lowest:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Intersection " << idx[i] + 1 << ": " << arr[i] << " congestion units" << endl;
    }
}

int main() {
    int size;
    cout << "Enter the number of intersections (max " << MAX_INTERSECTIONS << "): ";
    cin >> size;

    if (size > MAX_INTERSECTIONS) {
        cout << "Exceeds the maximum number of intersections." << endl;
        return 0;
    }

    int congestionLevels[size];  
    int intersectionIds[size]; 

    
    srand(time(0));

    cout << "Generating random congestion levels for " << size << " intersections:" << endl;
    for (int i = 0; i < size; i++) {
        congestionLevels[i] = rand() % 101; 
        intersectionIds[i] = i;  
        cout << "Intersection " << i + 1 << ": " << congestionLevels[i] << " congestion units" << endl;
    }

    
    mergeSort(congestionLevels, 0, size - 1, intersectionIds);

    
    displayCongestionLevels(congestionLevels, intersectionIds, size);

    int targetIntersection;
    cout << "\nEnter the intersection number to get the congestion level: ";
    cin >> targetIntersection;

    locateCongestionLevel(congestionLevels, intersectionIds, size, targetIntersection);

    return 0;
}
