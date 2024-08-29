#include<iostream>
#include<vector>
using namespace std;

template< typename T >
void maxSort(vector<T> &arr){

    //PORCENTAJE DE SOLUCION = 60-70%
    // int max = INT_MIN;
    // int count = 0;

    // int pos = arr.size() - count;
    /*La forma en que pos se calculaba y usaba no era dinámica; siempre apuntaba 
    a la misma posición sin actualizarse correctamente para reflejar el progreso 
    del ordenamiento.*/

    // for(int i = 0; i < pos; i++){
    //     if(arr[i] > max){
    //         max = i;
    //     }
    // }

    // swap(max, arr[pos]);
    /*Es fundamental comprender que, para mover un valor dentro de un array, 
    necesitas conocer su índice, no solo el valor. Esto te permitirá intercambiar 
    correctamente los elementos en el array. */

    // count++;
    /*Aunque incrementaste count, solo llamaste a maxSort una vez, por lo que count 
    no tuvo un efecto real en la lógica.*/

    int n = arr.size();
    for (int count = 0; count < n - 1; count++) {
        int maxIndex = 0;  // Para almacenar la posición del máximo valor
        for (int i = 1; i < n - count; i++) {
            if (arr[i] > arr[maxIndex]) {
                maxIndex = i;
            }
        }
        // Intercambiar el máximo valor encontrado con la última posición no ordenada
        swap(arr[maxIndex], arr[n - 1 - count]);
    }
}


int main(){
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    int arr_size = arr.size();

    cout << "Arreglo original: \n";
    for (int i = 0; i < arr_size; i++)
        cout << arr[i] << " ";
    cout << endl;

    maxSort(arr);

    cout << "Arreglo ordenado: \n";
    for (int i = 0; i < arr_size; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}