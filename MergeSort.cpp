#include <iostream>
using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void displayCongestionLevels(int arr[], int size) {
    cout << "Congestion levels (sorted from lowest to highest):" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Area " << i + 1 << ": " << arr[i] << " congestion units" << endl;
    }
}

int main() {
    int congestionLevels[] = {40, 10, 60, 30, 20};  // Example traffic congestion levels in different areas
    int size = sizeof(congestionLevels) / sizeof(congestionLevels[0]);

    mergeSort(congestionLevels, 0, size - 1);
    displayCongestionLevels(congestionLevels, size);

    return 0;
}
