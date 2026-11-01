#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <string>
#include <vector>
 
// QuickSort sobre std::vector<std::string>, ordena v[bajo..alto] (inclusive).
// Pivote aleatorio + particion de 3 vias + recursion solo sobre la mitad menor
// (profundidad de pila garantizada O(log n)).
void quickSort(std::vector<std::string>& v, int bajo, int alto);

#endif
