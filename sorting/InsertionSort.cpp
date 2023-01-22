#include <bits/stdc++.h>
using namespace std;

void insertionSort(vector<int> &A){
    int n = A.size();
    for(int i=1; i < n; i++){
        int key = A[i];
        int j = i - 1;
        while(j >= 0 && A[j] > key){
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key;
    }
}