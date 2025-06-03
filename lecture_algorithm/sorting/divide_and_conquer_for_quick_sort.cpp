#include <iostream>
#include <vector>
#include <cstdlib>  // for rand()
#include <ctime>    // for srand()

using namespace std;

void partition(vector<int>& S, int pivotIndex,
               vector<int>& L, vector<int>& E, vector<int>& G) {
    // 1. 피벗 선택 후 S에서 제거
    int x = S[pivotIndex];
    S.erase(S.begin() + pivotIndex);

    // 2. S가 빌 때까지 반복
    while (!S.empty()) {
        int y = S.front();            // S.first()
        S.erase(S.begin());          // S.remove(S.first())

        // 조건 분기 (y와 피벗 x 비교)
        if (y < x)
            L.push_back(y);          // L.insertLast(y)
        else if (y == x)
            E.push_back(y);          // E.insertLast(y)
        else
            G.push_back(y);          // G.insertLast(y)
    }

    // 3. pivot x는 E에 삽입
    E.push_back(x);
}

// QuickSort 함수 (Divide and Conquer)
vector<int> quickSort(vector<int> S) {
    // 이미 정렬된 상태
    if (S.size() <= 1)
        return S;

    // Divide: 무작위 pivot 선택 및 분할
    int pivotIndex = rand() % S.size();
    vector<int> L, E, G;
    partition(S, pivotIndex, L, E, G);

    // Conquer: 재귀적으로 정렬 후 병합
    vector<int> sortedL = quickSort(L);
    vector<int> sortedG = quickSort(G);

    // Combine: sortedL + E + sortedG
    sortedL.insert(sortedL.end(), E.begin(), E.end());
    sortedL.insert(sortedL.end(), sortedG.begin(), sortedG.end());

    return sortedL;
}

int main() {
    srand(time(0));  // 랜덤 시드 초기화
    vector<int> arr = {5, 3, 8, 4, 2, 7, 1, 10, 5, 3};

    vector<int> sorted = quickSort(arr);

    cout << "Sorted array: ";
    for (int val : sorted)
        cout << val << " ";
    cout << endl;

    return 0;
}