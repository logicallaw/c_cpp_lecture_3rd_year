#include <iostream>
#include <vector>
using namespace std;

void Merge(vector<int>& A, vector<int>& B, vector<int>& C);

void MergeSort(int arr[], int first, int last) {
    if (first < last) {
        int mid = (first+last)/2;
        vector<int> left(arr + first, arr + mid + 1);
        vector<int> right(arr + mid + 1, arr + last + 1);

        // Recursively sort left and right parts
        MergeSort(left.data(), 0, left.size() - 1);
        MergeSort(right.data(), 0, right.size() - 1);

        vector<int> merged;
        Merge(left, right, merged);
        for (size_t i = 0; i < merged.size(); ++i) {
            arr[first + i] = merged[i];
        }
    }
}

void Merge(vector<int>& A, vector<int>& B, vector<int>& C) {
    if (A.empty()) {
        C.insert(C.end(), B.begin(), B.end());
        return;
    } else if (B.empty()) {
        C.insert(C.end(), A.begin(), A.end());
        return;
    } else if (A.front() <= B.front()) {
        C.push_back(A.front());
        A.erase(A.begin());
        Merge(A, B, C);
    } else {
        C.push_back(B.front());
        B.erase(B.begin());
        Merge(A, B, C);
    }
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    MergeSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;  
}