#include<iostream>
#include<vector>
using namespace std;

template< typename T >
void maxElement(vector<T> &arr, int n, int count){
    int maxIndex = 0;  // Almacenar la posición del valor máximo 
    for (int i = 1; i < n - count; i++) {
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i; //Obtener la posición del valor máximo 
        }
    }
    // Intercambiar el valor máximo encontrado con la última posición no ordenada
    swap(arr[maxIndex], arr[n - 1 - count]);
}

template< typename T >
void maxSort(vector<T> &arr, int n){
    for (int count = 0; count < n - 1; count++) { //Repetir n veces la busqueda del elemento máximo para poder ordenar el arreglo
        maxElement(arr, n, count);
    }
}

template< typename T >
void printArray(vector<T> arr, int n){
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}


int main(){
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    int arr_size = arr.size();

    printArray(arr, arr_size);

    maxSort(arr, arr_size);

    printArray(arr, arr_size);

    return 0;
}


    /*---------------------RECOMENDACIONES/*---------------------*/
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