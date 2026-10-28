#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <chrono>
#include <cstdlib>
#include <ctime>
#include "quickSort.h"
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
auto inicio = chrono::high_resolution_clock::now();
quickSort(palabras, 0, (int)palabras.size() - 1);
auto fin = chrono::high_resolution_clock::now();

chrono::duration<double, milli> duracion = fin - inicio;
cout << "Tiempo QuickSort: " << duracion.count() << " ms" << endl;
return 0;


}