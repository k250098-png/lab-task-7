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

void alternateSort(int arr[], int low, int high, int level, int& subarrays) {
    if (low >= high) return;

    if (level % 2 != 0) {
        // Odd Level: Quick Sort Partition
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j] < pivot) {
                i++;
                swapElements(arr[i], arr[j]);
            }
        }
        swapElements(arr[i + 1], arr[high]);
        int pivot_idx = i + 1;
        
        subarrays += 2;
        cout << "Level " << level << " (Quick Sort) - Pivot: " << pivot << " -> Subarrays: ";
        printArray(arr, low, pivot_idx - 1);
        cout << ", ";
        printArray(arr, pivot_idx + 1, high);
        cout << "\n";
        
        alternateSort(arr, low, pivot_idx - 1, level + 1, subarrays);
        alternateSort(arr, pivot_idx + 1, high, level + 1, subarrays);
    } else {
        // Even Level: Merge Sort Division
        int mid = low + (high - low) / 2;
        subarrays += 2;
        
        cout << "Level " << level << " (Merge Sort) -> Subarrays: ";
        printArray(arr, low, mid);
        cout << ", ";
        printArray(arr, mid + 1, high);
        cout << "\n";
        
        alternateSort(arr, low, mid, level + 1, subarrays);
        alternateSort(arr, mid + 1, high, level + 1, subarrays);
        
        int temp[50]; 
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
    }
}

int main() {
    int products[] = {105, 120, 115, 130, 102, 199, 145, 155, 160, 111, 
                      177, 188, 122, 134, 142, 150, 165, 172, 184, 195};
    int n = sizeof(products) / sizeof(products[0]);
    int total_subarrays = 0;
    
    alternateSort(products, 0, n - 1, 1, total_subarrays);
    cout << "Total Subarrays Generated: " << total_subarrays << "\n";
    cout << "Final Sorted Inventory: ";
    printArray(products, 0, n - 1);
    cout << "\n";
    return 0;
}
