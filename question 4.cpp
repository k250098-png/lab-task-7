#include <iostream>
using namespace std;

void printBinary(int n, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        int k = n >> i;
        if (k & 1) cout << "1";
        else cout << "0";
    }
}

int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSortBinary(int arr[], int n, int bit_pos, int pass_num) {
    int output[20]; // Sufficient capacity
    int count[2] = {0, 0};

    for (int i = 0; i < n; i++) {
        int bit = (arr[i] >> bit_pos) & 1;
        count[bit]++;
    }

    int zeros = count[0], ones = count[1];
    count[1] += count[0];

    for (int i = n - 1; i >= 0; i--) {
        int bit = (arr[i] >> bit_pos) & 1;
        output[count[bit] - 1] = arr[i];
        count[bit]--;
    }

    for (int i = 0; i < n; i++) arr[i] = output[i];

    cout << "Pass " << pass_num << " - Bit Position " << bit_pos << "\n";
    cout << "Zeros: " << zeros << " | Ones: " << ones << "\n";
    cout << "Decimal: ";
    for(int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\nBinary: ";
    for(int i = 0; i < n; i++) {
        printBinary(arr[i], 4); 
        cout << " ";
    }
    cout << "\n\n";
}

int getBitLength(int n) {
    int bits = 0;
    while(n > 0) { bits++; n >>= 1; }
    return bits;
}

int countSetBits(int n) {
    int count = 0;
    while(n) { count += n & 1; n >>= 1; }
    return count;
}

int main() {
    int arr[] = {12, 5, 9, 3, 12, 7, 8, 15, 6, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int max_val = getMax(arr, n);
    int bit_length = getBitLength(max_val);

    for (int bit_pos = 0; bit_pos < bit_length; bit_pos++) {
        countSortBinary(arr, n, bit_pos, bit_pos + 1);
    }

    int max_set_bits = countSetBits(max_val);
    int same_set_bits_count = 0;
    for(int i = 0; i < n; i++) {
        if(countSetBits(arr[i]) == max_set_bits) same_set_bits_count++;
    }

    cout << "--- Additional Analysis ---\n";
    cout << "Longest Binary Representation: " << max_val << " = ";
    printBinary(max_val, bit_length);
    cout << " (Length: " << bit_length << " bits)\n";
    
    cout << "Largest Input Value: " << max_val << " = ";
    printBinary(max_val, bit_length);
    cout << " (Set bits: " << max_set_bits << ")\n";
    
    cout << "Numbers with same number of set bits count: " << same_set_bits_count << "\n";

    return 0;
}
