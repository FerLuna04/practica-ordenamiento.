// Genera dataset.txt: N palabras aleatorias (sin repetir) tomadas de words_alpha.txt
// Compilar: g++ -O2 -std=c++17 generar_dataset.cpp -o generar_dataset
// Uso:      ./generar_dataset words_alpha.txt dataset.txt 100000
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    string entrada = argc > 1 ? argv[1] : "words_alpha.txt";
    string salida  = argc > 2 ? argv[2] : "dataset.txt";
    size_t n       = argc > 3 ? stoul(argv[3]) : 100000;

    ifstream in(entrada);
    if (!in) { cerr << "No se pudo abrir " << entrada << endl; return 1; }

    vector<string> todas;
    string l;
    while (getline(in, l)) {
        while (!l.empty() && (l.back() == '\r' || l.back() == ' ')) l.pop_back();
        if (!l.empty()) todas.push_back(l);
    }
    if (todas.size() < n) { cerr << "Solo hay " << todas.size() << " palabras" << endl; return 1; }

    mt19937 gen(random_device{}());
    // Fisher-Yates parcial: solo se barajan las primeras n posiciones -> O(n)
    for (size_t i = 0; i < n; i++) {
        size_t j = i + gen() % (todas.size() - i);
        swap(todas[i], todas[j]);
    }

    ofstream out(salida, ios::binary);   // binario: fuerza '\n' (sin CRLF)
    for (size_t i = 0; i < n; i++) out << todas[i] << '\n';
    cout << "Generado " << salida << " con " << n << " palabras aleatorias" << endl;
    return 0;
}
