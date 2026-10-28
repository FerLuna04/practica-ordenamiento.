#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<string> palabras;
    ifstream archivo("dataset.txt");
    
    if (!archivo.is_open()) {
        cout << "No se pudo abrir dataset.txt" << endl;
        return 1;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
        palabras.push_back(linea);
    }
 }
archivo.close();


cout << "Palabras leidas: " << palabras.size() << endl;
return 0;


}