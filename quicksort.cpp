#include "quicksort.h"
#include <random>
#include <utility>
using namespace std;

static mt19937 rng(12345);  // semilla fija -> corridas reproducibles

// Para subarreglos pequenos la insercion es mas rapida que seguir recursando
static void insercion(vector<string>& v, int bajo, int alto) {
    for (int i = bajo + 1; i <= alto; i++) {
        string clave = std::move(v[i]);
        int j = i - 1;
        while (j >= bajo && v[j] > clave) {
            v[j + 1] = std::move(v[j]);
            j--;
        }
        v[j + 1] = std::move(clave);
    }
}

void quickSort(vector<string>& v, int bajo, int alto) {
    while (bajo < alto) {
        if (alto - bajo < 16) {
            insercion(v, bajo, alto);
            return;
        }

        // Pivote aleatorio (copia: no puede moverse durante la particion)
        string pivote = v[bajo + (int)(rng() % (unsigned)(alto - bajo + 1))];

        // Particion de 3 vias (Dijkstra): [bajo,lt) < pivote | [lt,i) == | (gt,alto] >
        int lt = bajo, i = bajo, gt = alto;
        while (i <= gt) {
            int c = v[i].compare(pivote);
            if (c < 0)      swap(v[lt++], v[i++]);
            else if (c > 0) swap(v[i], v[gt--]);
            else            i++;
        }

        // Recursion sobre la parte mas pequena, iteracion sobre la mas grande
        if (lt - bajo < alto - gt) {
            quickSort(v, bajo, lt - 1);
            bajo = gt + 1;
        } else {
            quickSort(v, gt + 1, alto);
            alto = lt - 1;
        }
    }
}
