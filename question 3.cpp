#include <iostream>
using namespace std;

int getDigitSum(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSortQ3(int arr[], int n, int exp, int pass_num) {
    int output[20]; 
    int count[10] = {0};
    int even_digit_count = 0;

    for (int i = 0; i < n; i++) {
        int index = (arr[i] / exp) % 10;
        count[index]++;
        if (index % 2 == 0) even_digit_count++;
    }

    for (int i = 1; i < 10; i++) count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int index = (arr[i] / exp) % 10;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }

    for (int i = 0; i < n; i++) arr[i] = output[i];

    cout << "Pass " << pass_num << " (Exp " << exp << ") - Even digits count: " << even_digit_count << "\n";
    cout << "Updated Array: [";
    for(int i = 0; i < n; ++i) cout << arr[i] << (i < n-1 ? ", " : "");
    cout << "]\n";
}

void radixSortQ3(int arr[], int n) {
    int max_val = getMax(arr, n);
    int pass_num = 1;
    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        countSortQ3(arr, n, exp, pass_num++);
    }
}

int main() {
    int ids[] = {1234, 5678, 1234, 4321, 8765, 9999, 1111, 2468, 1357, 2468,
                 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 1234};
    int n = sizeof(ids) / sizeof(ids[0]);

    radixSortQ3(ids, n);

  
    int freq[10000] = {0};
    for(int i = 0; i < n; i++) {
        freq[ids[i]]++;
    }
    
    cout << "\nDuplicates:\n";
    for(int i = 0; i < 10000; i++) {
        if(freq[i] > 1) {
            cout << i << ": " << freq[i] << " times\n";
        }
    }

    int max_sum = 0, max_id = 0;
    for(int i = 0; i < n; i++) {
        int sum = getDigitSum(ids[i]);
        if(sum > max_sum) { max_sum = sum; max_id = ids[i]; }
    }
    cout << "ID with highest digit sum: " << max_id << " (Sum: " << max_sum << ")\n";

    int max_seq_len = 0, current_seq_len = 0;
    int max_seq_start = 0, current_seq_start = 0;

    for(int i = 0; i < n; i++) {
        if(getDigitSum(ids[i]) % 2 == 0) {
            if (current_seq_len == 0) current_seq_start = i;
            current_seq_len++;
            if(current_seq_len > max_seq_len) {
                max_seq_len = current_seq_len;
                max_seq_start = current_seq_start;
            }
        } else {
            current_seq_len = 0;
        }
    }
    
    cout << "Longest sequence of even digit sums (Length: " << max_seq_len << "): [";
    for(int i = 0; i < max_seq_len; ++i) {
        cout << ids[max_seq_start + i] << (i < max_seq_len - 1 ? ", " : "");
    }
    cout << "]\n";

    return 0;
}
