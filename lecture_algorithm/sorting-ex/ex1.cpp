#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void partition(vector<int>& S, int pivotIndex,
vector<int>& L, vector<int>& E, vector<int>& G) {
    int x = S[pivotIndex];
    S.erase(S.begin() + pivotIndex);

    while(!S.empty()) {
        int y = S.front();
        S.erase(S.begin());
        if (y < x) {
            L.push_back(y);
        } else if (y == x) {
            E.push_back(y);
        } else {
            G.push_back(y);
        }
    }
    E.push_back(x);
}

vector<int> quickSort(vector<int> S) {
    if (S.size() <= 1) {
        return S;
    }

    int pivotIndex = rand() % S.size();
    vector<int> L, E, G;
    partition(S, pivotIndex, L, E, G);

    vector<int> sortedL = quickSort(L);
    vector<int> sortedG = quickSort(G);

    sortedL.insert(sortedL.end(), E.begin(), E.end());
    sortedL.insert(sortedL.end(), sortedG.begin(), sortedG.end());

    return sortedL;
}

int main() {
    srand(time(0));
    vector<int> arr = {5, 3, 8, 4, 2, 7, 1, 10, 5, 3};

    vector<int> sorted = quickSort(arr);

    for (int val: sorted) {
        cout << val << " ";
    }

    cout << endl;
    return 0;
}