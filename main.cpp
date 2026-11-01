#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "avltree.h"
#include "heapsort.h"
#include "quicksort.h"
#include "utils.h"
using namespace std;

struct Resultado {
    string nombre;
    double msMin = 1e18, msProm = 0;
    size_t memBytes = 0;
    bool ok = false;
};

static void imprimirPrimeras(const vector<string>& v, int n = 10) {
    for (int i = 0; i < n && i < (int)v.size(); i++) cout << "  " << v[i] << "\n";
}

int main(int argc, char** argv) {
    string ruta = argc > 1 ? argv[1] : "dataset.txt";
    int corridas = argc > 2 ? max(1, atoi(argv[2])) : 5;

    vector<string> original = leerDataset(ruta);
    if (original.empty()) {
        cout << "No se pudo leer " << ruta << " (o esta vacio)\n";
        return 1;
    }
    const size_t n = original.size();
    cout << "Palabras leidas: " << n << " | corridas por algoritmo: " << corridas << "\n";
    cout << "Dataset ya ordenado de antemano? " << (estaOrdenado(original) ? "SI (aleatorizar!)" : "NO (aleatorio)") << "\n\n";

    Resultado rq{"QuickSort"}, rh{"HeapSort"}, ra{"AVL + inorder"};
    vector<string> salidaQ, salidaH, salidaA;
    int alturaAVL = 0;
    size_t nodosAVL = 0;

    for (int c = 0; c < corridas; c++) {
        // --- QuickSort: cada algoritmo recibe SU copia del mismo orden aleatorio ---
        vector<string> q = original;
        Cronometro t1;
        quickSort(q, 0, (int)q.size() - 1);
        double mq = t1.ms();

        // --- HeapSort ---
        vector<string> h = original;
        Cronometro t2;
        heapSort(h);
        double mh = t2.ms();

        // --- AVL: insercion de las n palabras + recorrido inorder a una lista ---
        vector<string> a;
        double ma;
        {
            Cronometro t3;
            AVLTree arbol;
            for (const auto& w : original) arbol.insert(w);
            a = arbol.inorder();
            ma = t3.ms();
            alturaAVL = arbol.treeHeight();
            nodosAVL = arbol.nodeCount();
        }

        rq.msMin = min(rq.msMin, mq); rq.msProm += mq / corridas;
        rh.msMin = min(rh.msMin, mh); rh.msProm += mh / corridas;
        ra.msMin = min(ra.msMin, ma); ra.msProm += ma / corridas;

        if (c == corridas - 1) { salidaQ.swap(q); salidaH.swap(h); salidaA.swap(a); }
    }

    // ---------------- Verificacion de correctitud ----------------
    rq.ok = estaOrdenado(salidaQ) && salidaQ.size() == n;
    rh.ok = estaOrdenado(salidaH) && salidaH.size() == n;
    ra.ok = estaOrdenado(salidaA) && salidaA.size() == n;
    bool iguales = (salidaQ == salidaH) && (salidaH == salidaA);

    cout << "=== Verificacion ===\n";
    cout << "QuickSort ordenado : " << (rq.ok ? "SI" : "NO") << "\n";
    cout << "HeapSort  ordenado : " << (rh.ok ? "SI" : "NO") << "\n";
    cout << "AVL       ordenado : " << (ra.ok ? "SI" : "NO") << "\n";
    cout << "Las 3 salidas son identicas: " << (iguales ? "SI" : "NO") << "\n\n";
    cout << "Primeras 10 palabras ordenadas:\n";
    imprimirPrimeras(salidaQ);
    cout << "Ultimas 3 palabras:\n";
    for (size_t i = n >= 3 ? n - 3 : 0; i < n; i++) cout << "  " << salidaQ[i] << "\n";

    // ---------------- Estimacion de memoria (bytes) ----------------
    // QuickSort: vector + buffers de strings largos + pila O(log n) (~ 2*log2(n) marcos de ~96 B)
    size_t datos = bytesVectorStrings(original);
    size_t log2n = 0;
    for (size_t k = n; k > 1; k >>= 1) log2n++;
    size_t pilaQ = 2 * log2n * 96;
    rq.memBytes = datos + pilaQ + sizeof(string);                 // + copia del pivote
    // HeapSort: in-place, solo variables locales
    rh.memBytes = datos;
    // AVL: n nodos individuales + overhead malloc + strings largos + vector de salida (otra copia)
    size_t nodos = nodosAVL * (sizeof(AVLNode) + OVERHEAD_MALLOC);
    size_t salida = bytesVectorStrings(salidaA);
    ra.memBytes = nodos + bytesHeapStrings(original) + salida;

    cout << "\n=== Memoria estimada ===\n";
    cout << "sizeof(string)=" << sizeof(string) << " B | sizeof(AVLNode)=" << sizeof(AVLNode)
         << " B | altura AVL=" << alturaAVL << " (log2 n = " << log2n << ", cota 1.44*log2(n) ~ "
         << (int)(1.44 * (double)log2n) << ")\n";
    cout << "Datos base (vector<string>): " << datos / 1024 << " KB\n";

    // ---------------- Tabla comparativa ----------------
    cout << "\n=== Comparacion (n = " << n << ") ===\n";
    cout << left << setw(16) << "Algoritmo" << setw(26) << "Complejidad tiempo"
         << setw(14) << "Espacio aux." << right << setw(12) << "Min (ms)" << setw(12) << "Prom (ms)"
         << setw(14) << "Mem (KB)" << "\n";
    cout << string(94, '-') << "\n";
    cout << fixed << setprecision(2);
    auto fila = [&](const Resultado& r, const char* tiempo, const char* esp) {
        cout << left << setw(16) << r.nombre << setw(26) << tiempo << setw(14) << esp << right
             << setw(12) << r.msMin << setw(12) << r.msProm << setw(14) << r.memBytes / 1024 << "\n";
    };
    fila(rq, "O(n log n) prom / O(n^2)", "O(log n)");
    fila(rh, "O(n log n) siempre", "O(1)");
    fila(ra, "O(n log n) siempre", "O(n)");

    vector<const Resultado*> r{&rq, &rh, &ra};
    sort(r.begin(), r.end(), [](auto* x, auto* y) { return x->msProm < y->msProm; });
    const Resultado* menosMem = &rq;
    for (auto* x : r) if (x->memBytes < menosMem->memBytes) menosMem = x;

    cout << "\nMas rapido (prom): " << r[0]->nombre << " | Mas lento: " << r[2]->nombre
         << " (" << r[2]->msProm / r[0]->msProm << "x)\n";
    cout << "Menor memoria: " << menosMem->nombre << "\n";

    cout << "\n=== Analisis (tendencias tipicas; contrastar con la tabla de arriba) ===\n"
         << "1) Las tres estrategias son O(n log n); lo que cambia son las constantes. QuickSort recorre\n"
         << "   el arreglo de forma secuencial (buena localidad de cache) y hace pocas comparaciones.\n"
         << "2) HeapSort salta entre i, 2i+1, 2i+2 (peor localidad) y hace ~2 comparaciones por nivel en\n"
         << "   sift-down; suele perder frente a QuickSort, pero garantiza O(n log n) en el peor caso con\n"
         << "   O(1) de memoria auxiliar.\n"
         << "3) El AVL reparte n nodos sueltos con punteros (cache misses), hace n inserciones con\n"
         << "   rotaciones y copia todo en el inorder. Es el que mas memoria usa: nodo (clave + 2\n"
         << "   punteros + altura) + malloc por nodo + vector de salida.\n"
         << "4) Teoria vs practica: Big O oculta constantes, jerarquia de memoria y asignaciones dinamicas.\n"
         << "5) Uso recomendado: QuickSort para ordenar un arreglo una sola vez; HeapSort si se exige\n"
         << "   peor caso garantizado con memoria minima; AVL si ademas se necesitan inserciones,\n"
         << "   busquedas y borrados dinamicos manteniendo el orden.\n";
    return 0;
}
