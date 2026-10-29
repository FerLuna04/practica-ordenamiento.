#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <chrono>
#include <cstdlib>
#include <ctime>
#include "quicksort.h"
#include "heapsort.h"
using namespace std;

int main() {
    srand(time(0));
    vector<string> palabras;
    ifstream archivo("dataset.txt");
    
    if (!archivo.is_open()) {
        cout << "No se pudo abrir dataset.txt" << endl;
        return 1;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
        palabras.push_back(linea);
    }
 }
archivo.close();


cout << "Palabras leidas: " << palabras.size() << endl;

vector<string> paraHeap = palabras;   // copia desordenada para HeapSort
auto inicio = chrono::high_resolution_clock::now();
quickSort(palabras, 0, (int)palabras.size() - 1);
auto fin = chrono::high_resolution_clock::now();

chrono::duration<double, milli> duracion = fin - inicio;
cout << "Tiempo QuickSort: " << duracion.count() << " ms" << endl;
    // Verificar que quedo ordenado
    bool ordenado = true;
    for (size_t i = 1; i < palabras.size(); i++) {
        if (palabras[i - 1] > palabras[i]) {
            ordenado = false;
            break;
        }
    }
    cout << "Ordenado correctamente: " << (ordenado ? "SI" : "NO") << endl;

    cout << "Primeras 10 palabras:" << endl;
    for (int i = 0; i < 10 && i < (int)palabras.size(); i++) {
        cout << palabras[i] << endl;
    }
        // Estimacion de memoria
    size_t memoriaVector = palabras.size() * sizeof(string);
    size_t memoriaExtra = 0;
    for (size_t i = 0; i < palabras.size(); i++) {
        if (palabras[i].capacity() > 15) {
            memoriaExtra += palabras[i].capacity() + 1;
        }
    }
    cout << "sizeof(string): " << sizeof(string) << " bytes" << endl;
    cout << "Memoria del vector: " << memoriaVector / 1024 << " KB" << endl;
    cout << "Memoria extra (palabras largas): " << memoriaExtra / 1024 << " KB" << endl;
    cout << "Memoria total aprox: " << (memoriaVector + memoriaExtra) / 1024 << " KB" << endl;


auto inicioHeap = chrono::high_resolution_clock::now();
heapSort(paraHeap);
auto finHeap = chrono::high_resolution_clock::now();

chrono::duration<double, milli> duracionHeap = finHeap - inicioHeap;
cout << "Tiempo HeapSort: " << duracionHeap.count() << " ms" << endl;
bool ordenadoHeap = true;
for (size_t i = 1; i < paraHeap.size(); i++) {
    if (paraHeap[i - 1] > paraHeap[i]) {
        ordenadoHeap = false;
        break;
    }
}
cout << "HeapSort ordenado correctamente: " << (ordenadoHeap ? "SI" : "NO") << endl;
return 0;


}