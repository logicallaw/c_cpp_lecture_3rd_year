#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// In-place partition with 3-way split using two pointers
pair<int, int> inPlacePartition(vector<int>& S, int l, int r) {
    int pivot = S[l];  // pivot은 S[l] (랜덤 선택은 외부에서)
    int i = l;
    int j = l;
    int k = r;

    while (j <= k) {
        // 나보다 
        if (S[j] < pivot) {
            swap(S[i], S[j]);
            i++;
            j++;
        } else if (S[j] > pivot) {
            swap(S[j], S[k]);
            k--;
        } else { // S[j] == pivot
            j++;
        }
    }
    // 반환값은 pivot 범위 [i, k]
    return {i, k};
}

// In-place randomized quick sort
void inPlaceQuickSort(vector<int>& S, int l, int r) {
    if (l >= r)
        return;

    // 랜덤 pivot 선택 및 첫 요소로 이동
    int pivotIndex = l + rand() % (r - l + 1);
    swap(S[l], S[pivotIndex]);

    pair<int, int> range = inPlacePartition(S, l, r);
    int h = range.first;
    int k = range.second;

    inPlaceQuickSort(S, l, h - 1);
    inPlaceQuickSort(S, k + 1, r);
}

int main() {
    srand(time(0));  // 랜덤 시드 초기화

    vector<int> arr = {3, 2, 5, 1, 0, 7, 3, 5, 9, 2, 7, 9, 8, 9, 7, 6, 6, 9};

    inPlaceQuickSort(arr, 0, arr.size() - 1);

    cout << "Sorted array: ";
    for (int val : arr)
        cout << val << " ";
    cout << endl;

    return 0;
}