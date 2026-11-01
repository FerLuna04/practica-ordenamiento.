#include "heapsort.h"
#include <utility>
using namespace std;

BinaryHeap::BinaryHeap(vector<string>& datos) : a(datos), tam(datos.size()) {
    // Floyd: sift-down desde el ultimo nodo interno hasta la raiz -> O(n)
    for (size_t i = tam / 2; i-- > 0;) siftDown(i);
}

// Iterativo (sin recursion). Compara con el mayor de los hijos.
void BinaryHeap::siftDown(size_t i) {
    while (true) {
        size_t izq = 2 * i + 1, der = izq + 1, mayor = i;
        if (izq < tam && a[izq] > a[mayor]) mayor = izq;
        if (der < tam && a[der] > a[mayor]) mayor = der;
        if (mayor == i) break;
        swap(a[i], a[mayor]);
        i = mayor;
    }
}

void BinaryHeap::extractMaxToEnd() {
    if (tam == 0) return;
    swap(a[0], a[tam - 1]);
    tam--;
    siftDown(0);
}

void heapSort(vector<string>& v) {
    BinaryHeap heap(v);
    while (heap.size() > 1) heap.extractMaxToEnd();
}
