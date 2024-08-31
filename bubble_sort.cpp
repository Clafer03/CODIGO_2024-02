#include<iostream>
#include<vector>
using namespace std;

template <typename T>
void bubbleSort(vector<T> & arr){
    int n = arr.size();
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if( arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

template< typename T >
void printArray(vector<T> arr){
    for (auto i : arr)
        cout << i << " ";
    cout << endl;
}

int main(){
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    printArray(arr);
    bubbleSort(arr);
    printArray(arr);
}