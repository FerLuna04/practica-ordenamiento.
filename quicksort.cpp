#include "quicksort.h"
#include <cstdlib>
#include <utility>
using namespace std;
//Reorganiza el vector alrededor de un pivote aleatorio
// y devuelve la posicion final del pivote
static int particionar(vector<string>& v, int bajo, int alto) {
    int indiceAleatorio = bajo + rand() % (alto - bajo + 1);
    swap(v[indiceAleatorio], v[alto]);

    string pivote = v[alto];
    int i = bajo - 1;

    for (int j = bajo; j < alto; j++) {
        if (v[j] < pivote) {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i +1], v[alto]);
    return i + 1;
    }

    void quickSort(vector<string>& v, int bajo, int alto) {
        if (bajo < alto) {
            int p = particionar(v, bajo, alto);
            quickSort(v, bajo, p - 1);
            quickSort(v, p + 1, alto);
        }
    }
