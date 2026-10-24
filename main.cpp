#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <utility>
using namespace std;
// Reorganiza el vector alrededor de un pivote y devuelve la posicion final del pivote//.
int particionar(vector<string>& v, int bajo, int alto){
    //Pivote aleatorio para evitar el peor caso
    int indiceAleatorio = bajo + rand() % (alto - bajo + 1);
    swap(v[indiceAleatorio], v[alto]);

    string pivote = v[alto];
    int i = bajo - 1;

    for (int j = bajo; j < alto; j++) {
        if (v[j] < pivote){
            i++; 
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[alto]);
    return i + 1;
}

void quickSort(vector<string>& v, int bajo, int alto) {
    if (bajo < alto) {
        int p = particionar(v, bajo, alto);
        quickSort(v,bajo, p - 1);
        quickSort(v, p + 1, alto);
    }
}

int main() {
    srand(time(0));

    vector<string> palabras;
    ifstream archivo("dataset.txt");

    if (!archivo.is_open()) {
        cout <<"No se pudo abrir dataset.txt"<< endl;
        return 1;
    }
        string linea;
    while (getline(archivo, linea)) {
        // Quitar espacios, tabulaciones y saltos al final
        while (!linea.empty() && (linea.back() == '\r' || linea.back() == ' ' || linea.back() == '\t')) {
            linea.pop_back();
        }
        // Quitar espacios al inicio
        size_t pos = 0;
        while (pos < linea.size() && (linea[pos] == ' ' || linea[pos] == '\t')) {
            pos++;
        }
        linea = linea.substr(pos);

        if (!linea.empty()) {
            palabras.push_back(linea);
        }
    }
    archivo.close();

    cout << "Palabras leidas (v2):" << palabras.size() << endl;

     // Ordenar y medir el tiempo
     auto inicio = chrono::high_resolution_clock::now();
     quickSort(palabras, 0, (int)palabras.size() - 1);
     auto fin = chrono::high_resolution_clock::now();

     chrono::duration<double, milli> duracion = fin - inicio;
     cout << "Tiempo QuickSort: " << duracion.count() << "ms" << endl;

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
      // Estimación memoria
      size_t memoriaVector = palabras.size() * sizeof(string);
      size_t memoriaExtra = 0;
      for (size_t i = 0; i < palabras.size(); i++) {
        if (palabras[i].capacity() > 15) {
            memoriaExtra += palabras[i].capacity() + 1;
        }
      }
      cout << "sizeof(string): " << sizeof(string) << "bytes" << endl;
      cout << "Memoria del vector: "<< memoriaVector / 1024 << " KB" << endl;
      cout << "Memoria extra (palabras largas): " << memoriaExtra / 1024 << " KB" << endl;
      cout << "Memoria total aprox: " << (memoriaVector + memoriaExtra) / 1024 << " KB" << endl;
      
      return 0; 
    }  