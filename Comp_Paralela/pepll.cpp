#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono> // Biblioteca para medir el tiempo

using namespace std;
using namespace chrono; // Para facilidad al usar time_point, duration, etc.

const int SIZE = 1000000; // Tamaño de los arreglos
vector<int> array1(SIZE);
vector<int> array2(SIZE);
int r2 = 0;
mutex mtx; // Mutex para sincronización

// Función para sumar segmentos de los arreglos
void sumArrays(int start, int end) {
    int r1 = 0;
    for (int i = start; i < end; ++i) {
        r1 = array1[i] * array2[i]; // Producto de los elementos
        // Bloqueo para sincronizar la suma
        lock_guard<mutex> lock(mtx);
        r2 += r1;
    }
}

int main() {
    // Inicializar los arreglos con valores de ejemplo
    for (int i = 0; i < SIZE; ++i) {
        array1[i] = i + 1;
        array2[i] = i - 1;
    }

    const int numThreads = 4; // Número de threads
    vector<thread> threads;
    int segmentSize = SIZE / numThreads;

    // Comenzar a medir el tiempo
    auto startTime = high_resolution_clock::now();

    // Crear y lanzar threads
    for (int i = 0; i < numThreads; ++i) {
        int start = i * segmentSize;
        int end = (i == numThreads - 1) ? SIZE : start + segmentSize; // Asegurar que el último thread cubra todo
        threads.push_back(thread(sumArrays, start, end));
    }

    // Esperar a que todos los threads terminen
    for (auto& th : threads) {
        th.join();
    }

    // Detener la medición del tiempo
    auto endTime = high_resolution_clock::now();
    duration<double> elapsed = endTime - startTime; // Tiempo transcurrido en segundos

    // Mostrar el resultado final del producto escalar
    cout << "El producto escalar de los vectores es: " << r2 << endl;
    cout << "Tiempo de ejecución: " << elapsed.count() << " segundos." << endl;

    return 0;
}
