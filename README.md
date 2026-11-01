# Práctica II – Ordenamiento de un dataset grande (C++)

**ST0245 – Estructuras de Datos y Algoritmos** · Universidad EAFIT

Programa en C++ que ordena **100.000 palabras en inglés** con tres estrategias distintas, y compara su **tiempo de ejecución**, **uso de memoria** y **complejidad**:

| Estrategia | Estructura de datos |
| --- | --- |
| QuickSort | `std::vector<std::string>` |
| HeapSort | Heap binario (max-heap implícito en arreglo) |
| Árbol AVL + recorrido inorder | Árbol binario de búsqueda balanceado |

No se usa `std::sort` ni ninguna función de ordenamiento de la librería estándar: los tres algoritmos están implementados desde cero.

## Integrantes

- Carlos Mario Monsalve Tangarife
- Luisa María Cuervo Prado
- Sheryl Astrid Murillo Duque
- Liceth Fernanda Luna Cañizales

## Estructura del repositorio

```
practica-ordenamiento/
├── main.cpp              # Programa principal: mide, verifica y compara los 3 métodos
├── quicksort.h / .cpp    # QuickSort sobre vector<string>
├── heapsort.h / .cpp     # Clase BinaryHeap + heapSort
├── avltree.h / .cpp      # Árbol AVL (inserción con rotaciones + inorder)
├── utils.h               # Lectura del dataset, cronómetro y estimación de memoria
├── generar_dataset.cpp   # Genera dataset.txt a partir de words_alpha.txt
├── dataset.txt           # 100.000 palabras aleatorias (entrada de los 3 algoritmos)
├── resultados.txt        # Salida de ejemplo de una ejecución
├── Makefile
└── informe.md            # Resumen del informe (el informe completo está en el .docx)
```

## Requisitos

- Compilador de C++ con soporte para C++17 (se probó con `g++` en MSYS2/Windows 11).
- `make` (opcional; también se puede compilar a mano).

## Compilar

Con `make`:

```bash
make
```

Esto genera los ejecutables `practica` (el programa principal) y `generar_dataset`.

Sin `make`:

```bash
g++ -O2 -std=c++17 -Wall -Wextra main.cpp quicksort.cpp heapsort.cpp avltree.cpp -o practica
```

> En Windows el ejecutable se llama `practica.exe`. Compila y ejecuta en comandos separados: si los pegas juntos, `g++` puede fallar con el error *"input file is the same as output file"*.

## Ejecutar

```bash
./practica [archivo] [corridas]
```

| Argumento | Descripción | Valor por defecto |
| --- | --- | --- |
| `archivo` | Ruta del dataset (una palabra por línea) | `dataset.txt` |
| `corridas` | Veces que se ejecuta cada algoritmo (se reporta mínimo y promedio) | `5` |

Ejemplos:

```bash
./practica                      # dataset.txt, 5 corridas
./practica dataset.txt 10       # 10 corridas por algoritmo
```

### Qué muestra el programa

1. Cantidad de palabras leídas y una comprobación de que el archivo **no** venga ya ordenado.
2. **Verificación de correctitud:** cada salida está ordenada alfabéticamente y las tres salidas son idénticas.
3. Las primeras 10 y las últimas 3 palabras ordenadas.
4. **Memoria estimada** con `sizeof` (vector, nodos del AVL, palabras largas, sobrecosto de `malloc`, pila de recursión) y la altura del AVL.
5. **Tabla comparativa:** complejidad, espacio auxiliar, tiempo mínimo y promedio (ms) y memoria (KB) de cada método.
6. Un análisis breve de los resultados.

## Generar un dataset nuevo (opcional)

`words_alpha.txt` viene ordenado alfabéticamente, así que hay que aleatorizarlo antes de ordenar. El repositorio ya incluye un `dataset.txt` listo; si quieres generar otro (descarga `words_alpha.txt` y ponlo en la misma carpeta):

```bash
./generar_dataset words_alpha.txt dataset.txt 100000
```

Selecciona `N` palabras distintas al azar con un Fisher-Yates parcial y las guarda con saltos de línea `\n`.

La lectura del dataset en `utils.h` es tolerante: quita el `\r` de los saltos de línea de Windows, ignora líneas vacías y acepta archivos con BOM UTF-8 o codificados en UTF-16.

## Resumen de la implementación

**QuickSort.** Pivote aleatorio y partición en tres zonas (menores, iguales, mayores), lo que evita el peor caso con datos ordenados o con palabras repetidas. Los rangos de menos de 16 elementos se terminan con ordenamiento por inserción, y solo se hace recursión sobre la zona más pequeña, así que la pila nunca pasa de O(log n). Ordena sobre el mismo vector, sin copias.

**HeapSort.** La clase `BinaryHeap` trabaja directamente sobre el vector. Construye el heap con el método de Floyd en O(n) y luego extrae el máximo n − 1 veces, cada una en O(log n). `siftDown` es iterativo y no se usa memoria extra.

**AVL.** Cada nodo guarda la palabra, los punteros a sus hijos y su altura. Tras cada inserción se recalcula el factor de balance y se aplican rotaciones simples o dobles según el factor de balance del hijo (no comparando palabras, para que el árbol siga balanceado con duplicados). Con las 100.000 palabras la altura queda en 20, dentro de la cota teórica ≈ 23. El inorder llena un vector reservado con el tamaño exacto, y los nodos se liberan en postorden.

## Resultados

Equipo: AMD Ryzen 5 3600 · 32 GB de RAM · Windows 11 Pro · `g++ 16.2.0` (MSYS2) con `-O2`.
Se ejecutó el programa 3 veces (5 corridas por algoritmo en cada una); los tiempos son el promedio de las 3 ejecuciones.

| Método | Tiempo promedio (ms) | Memoria aprox. (KB) |
| --- | --- | --- |
| QuickSort | 40,3 | 3.228 |
| HeapSort | 49,9 | 3.225 |
| AVL + inorder | 36,5 | 10.357 |

### Complejidad

| Método | Mejor caso | Caso promedio | Peor caso | Memoria extra |
| --- | --- | --- | --- | --- |
| QuickSort | O(n log n) | O(n log n) | O(n²) | O(log n) |
| HeapSort | O(n log n) | O(n log n) | O(n log n) | O(1) |
| AVL | O(n log n) | O(n log n) | O(n log n) | O(n) |

### Conclusiones

- El **AVL** fue el más rápido (36,5 ms), pero usó unas **3,2 veces más memoria** que los otros dos (un nodo con punteros por palabra, más el vector de salida del inorder).
- **QuickSort** quedó solo ~11 % por detrás del AVL y casi sin memoria extra, por lo que es el enfoque más adecuado para **ordenar una sola vez** un conjunto fijo de palabras.
- **HeapSort** fue el más lento, aunque garantiza O(n log n) en el peor caso sin memoria auxiliar.
- Las tres estrategias son O(n log n); la diferencia práctica viene de las constantes: costo de comparar y mover `string`, localidad de caché y asignación dinámica de memoria.
- El AVL gana su verdadero valor cuando, además de ordenar, hay que seguir **insertando o buscando** con los datos siempre ordenados.

El análisis completo (decisiones de diseño, tablas de memoria detalladas, problemas encontrados y uso de IA) está en el informe: **`Informe_Practica_Final_EDA.docx`**.

> Los tiempos dependen del equipo y del compilador; en otra máquina las cifras cambiarán y el orden entre QuickSort y AVL podría variar. `resultados.txt` es la salida de una ejecución individual.
