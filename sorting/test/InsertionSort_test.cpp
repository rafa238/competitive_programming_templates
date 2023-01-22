#include <bits/stdc++.h>
#include "../InsertionSort.cpp"

using namespace std;

void printArray(vector<int> A){
    for(auto e : A){
        cout << e << " ";
    }
    cout << endl;
}

int main(){
    vector<int> v = {5,6,2,1,10,98,123,8};
    insertionSort(v);
    printArray(v);
}
