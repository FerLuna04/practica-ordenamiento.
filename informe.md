# Práctica I – Ordenamiento de un dataset grande (C++)
ST0245 – Estructuras de Datos y Algoritmos | EAFIT

## 1. Enfoque de implementación
- Dataset: 100.000 palabras aleatorias tomadas de `words_alpha.txt` (`generar_dataset.cpp`, Fisher-Yates parcial).
- QuickSort: sobre `std::vector<std::string>`, pivote aleatorio, partición de 3 vías, insertion sort para subarreglos < 16, recursión sobre la mitad menor.
- HeapSort: clase `BinaryHeap` (max-heap implícito en arreglo), `buildHeap` O(n) y n extracciones O(log n), in-place.
- AVL: inserción de las 100.000 palabras con rotaciones (decisión por factor de balance del hijo), luego recorrido inorder guardado en un vector.
- Medición: `std::chrono::steady_clock`, 5 corridas por algoritmo sobre la misma copia desordenada; se reporta mínimo y promedio.

## 2. Mediciones (completar con TU máquina)
| Algoritmo | Min (ms) | Prom (ms) | Memoria est. (KB) |
|---|---|---|---|
| QuickSort | | | |
| HeapSort | | | |
| AVL + inorder | | | |

Equipo: CPU / RAM / SO / compilador y flags (`g++ -O2`).

## 3. Complejidad
| Algoritmo | Mejor | Promedio | Peor | Espacio auxiliar |
|---|---|---|---|---|
| QuickSort | O(n log n) | O(n log n) | O(n²) (mitigado con pivote aleatorio + 3 vías) | O(log n) |
| HeapSort | O(n log n) | O(n log n) | O(n log n) | O(1) |
| AVL + inorder | O(n log n) | O(n log n) | O(n log n) | O(n) |

## 4. Comparación y conclusiones
(Responder con tus números: ¿cuál fue más rápido?, ¿por qué la teoría difiere de la práctica?
—localidad de caché, constantes, `malloc` por nodo—, ventajas/desventajas de cada estructura.)

## 5. Conclusión
Para ordenar una sola vez un conjunto estático: ______ . Para datos dinámicos con consultas ordenadas: AVL.
