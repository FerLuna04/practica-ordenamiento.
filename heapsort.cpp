#include "heapsort.h"
#include <utility>
using namespace std;


static void heapify(vector<string>& v, int n, int i) {
    int mayor = i;
    int izq = 2 * i + 1;
    int der = 2 * i + 2;

    if (izq < n && v[izq] > v[mayor]) mayor = izq;
    if (der < n && v [der] > v[mayor]) mayor = der;

    if (mayor !=i){
        swap(v[i],  v[mayor]);
        heapify(v, n, mayor);
    }
}

void heapSort(std::vector<std::string>& v){
    int n = (int)v.size();

 // Construir el heap (reorganizar el vector)
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(v, n, i);
   }

   // Extraer el mayor repetidamente y reconstruir el heap
    for (int i = n - 1; i >= 1; i--){
        swap(v[0], v[i]);
        heapify(v, i, 0);
    }
}



