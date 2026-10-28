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