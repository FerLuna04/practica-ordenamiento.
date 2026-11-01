#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <cstddef>
#include <string>
#include <vector>

// Max-heap binario implicito (arreglo): hijos de i -> 2i+1 y 2i+2.
// Trabaja SOBRE el vector recibido (sin copias): memoria auxiliar O(1).
class BinaryHeap {
public:
    explicit BinaryHeap(std::vector<std::string>& datos);  // buildHeap: O(n)

    bool   empty() const { return tam == 0; }
    size_t size()  const { return tam; }

    // Mueve el maximo a la primera posicion libre al final (v[tam-1]) y
    // reduce el heap en 1. O(log n)
    void extractMaxToEnd();

private:
    std::vector<std::string>& a;
    size_t tam;
    void siftDown(size_t i);
};

// Ordena ascendentemente: buildHeap O(n) + n extracciones O(log n) = O(n log n)
void heapSort(std::vector<std::string>& v);

#endif
