#include <iostream>
using namespace std;

void printArray(const int arr[], int low, int high) {
    cout << "[";
    for (int i = low; i <= high; ++i) {
        cout << arr[i] << (i < high ? ", " : "");
    }
    cout << "]";
}

void swapElements(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition_q1(int arr[], int low, int high, int& subarrays) {
    int pivot = arr[high];
    cout << "Quick Sort - Selected Pivot: " << pivot << "\n";
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            i++;
            swapElements(arr[i], arr[j]);
        }
    }
    swapElements(arr[i + 1], arr[high]);
    
    subarrays += 2;
    cout << "Subarrays generated: ";
    printArray(arr, low, i);
    cout << " and ";
    printArray(arr, i + 2, high);
    cout << "\n";
    
    return i + 1;
}

void quickSort_q1(int arr[], int low, int high, int& subarrays) {
    if (low < high) {
        int pivot_idx = partition_q1(arr, low, high, subarrays);
        quickSort_q1(arr, low, pivot_idx - 1, subarrays);
        quickSort_q1(arr, pivot_idx + 1, high, subarrays);
    }
}

void mergeSort_q1(int arr[], int low, int high, int& subarrays) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        subarrays += 2;
        cout << "Merge Sort - Division Step: ";
        printArray(arr, low, mid);
        cout << " and ";
        printArray(arr, mid + 1, high);
        cout << "\n";

        mergeSort_q1(arr, low, mid, subarrays);
        mergeSort_q1(arr, mid + 1, high, subarrays);

        // Merge process using a temporary raw array
        int temp[50]; // Assume max size is enough for this task
        int i = low, j = mid + 1, k = 0;
        
        while (i <= mid && j <= high) {
            if (arr[i] <= arr[j]) temp[k++] = arr[i++];
            else temp[k++] = arr[j++];
        }
        while (i <= mid) temp[k++] = arr[i++];
        while (j <= high) temp[k++] = arr[j++];
        
        for (i = low, k = 0; i <= high; i++, k++) {
            arr[i] = temp[k];
        }
        
        cout << "Merge Sort - Merged Subarray: ";
        printArray(arr, low, high);
        cout << "\n";
    }
}

int main() {
    int original[] = {35, 33, 42, 10, 14, 19, 27, 44, 26, 31};
    int n = sizeof(original) / sizeof(original[0]);
    
    int arr_qs[10];
    int arr_ms[10];
    for (int i = 0; i < n; i++) {
        arr_qs[i] = original[i];
        arr_ms[i] = original[i];
    }
    
    int qs_subs = 0, ms_subs = 0;

    cout << "--- Quick Sort ---\n";
    quickSort_q1(arr_qs, 0, n - 1, qs_subs);
    cout << "Total Quick Sort subarrays: " << qs_subs << "\n\n";

    cout << "--- Merge Sort ---\n";
    mergeSort_q1(arr_ms, 0, n - 1, ms_subs);
    cout << "Total Merge Sort subarrays: " << ms_subs << "\n";
    return 0;
}
