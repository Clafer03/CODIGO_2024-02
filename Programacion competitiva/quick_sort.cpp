#include<iostream>
#include<vector>
using namespace std;

template <typename T>
int particion(vector<T> &arr, int p, int r){
    T x = arr[r];
    int i = p - 1;
    for(int j = p; j < r; j++){
        if(arr[j] <= x){
            i += 1;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[r]);
    return i+1;
}

template <typename T>
void quickSort(vector<T> &arr, int p, int r){
    if(p < r){
        int q = particion(arr, p, r);
        quickSort(arr, p, q-1);
        quickSort(arr, q+1, r);
    }
}   

int main() {
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    int arr_size = arr.size();

    cout << "Arreglo original: \n";
    for (int i = 0; i < arr_size; i++)
        cout << arr[i] << " ";
    cout << endl;

    quickSort(arr, 0, arr_size - 1);

    cout << "Arreglo ordenado: \n";
    for (int i = 0; i < arr_size; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}