#include <iostream>
using namespace std;

int shiftVacRec(int[], int, int);
void InsertionSort(int[], int);

int main() {
    int arr[6] = {5,2,4,6,1,3};

    InsertionSort(arr, 6);

    // Print nondecreasing ordered array
    for (int element : arr) {
        cout << element << " ";
    }
    cout << endl;

    return 0;
}

void InsertionSort(int arr[], int n) {
    int xindex;
    for (xindex = 1; xindex < n; xindex++) {
        int currentValue = arr[xindex];
        int xLoc = shiftVacRec(arr, xindex, currentValue);
        arr[xLoc] = currentValue;
    }
    return;
}

int shiftVacRec(int arr[], int vacant, int x) {
    int xLoc;
    if (vacant == 0) {
        xLoc = vacant;
    } else if (arr[vacant-1] <= x) {
        xLoc = vacant;
    } else {
        arr[vacant] = arr[vacant-1];
        xLoc = shiftVacRec(arr, vacant-1, x);
    }
    return xLoc;
}