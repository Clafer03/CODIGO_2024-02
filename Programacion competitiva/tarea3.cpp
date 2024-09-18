#include<iostream>
#include<vector>
using namespace std;


void eliminarElemento(vector<int> &v){
    int pos = 0;
    cout << "Ingrese la posición a eliminar: ";
    cin >> pos;
    if (pos >= 0 && pos < v.size()) {
        v.erase(v.begin() + pos);  // Complejidad O(n)
    } else {
        cout << "Posición inválida" << endl;
    }
}

void numeroMayor(vector<int> &v){
    int mayor = 0;
    for(int i = 0; i < v.size(); i++){
        if(mayor < v[i]){
            mayor = v[i];
        }
    }
    cout << mayor;
}

void imprimirVector(vector<int> &v){
    for(int i = 0; i < v.size(); i++){
        cout << v[i] <<", ";
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        // Encuentra el punto medio
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}



int main(){
    vector<int> v = {2,500,21,43,123,5,76,16};

    eliminarElemento(v);
    numeroMayor(v);
    mergeSort(v, 0, v.size() - 1);


    imprimirVector(v);

}