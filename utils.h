#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

// ---------------------------------------------------------------
// Lectura robusta del dataset:
//  - Quita '\r' (archivos con CRLF) para que no contaminen las palabras
//  - Tolera BOM UTF-8 y archivos UTF-16 LE/BE (ASCII) como el dataset.txt adjunto
//  - Ignora lineas vacias
// Complejidad: O(tamano del archivo)
// ---------------------------------------------------------------
inline std::vector<std::string> leerDataset(const std::string& ruta) {
    std::ifstream f(ruta, std::ios::binary);
    std::vector<std::string> palabras;
    if (!f.is_open()) return palabras;

    std::string raw((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

    // UTF-16: nos quedamos con el byte bajo de cada par (el corpus es ASCII)
    if (raw.size() >= 2) {
        unsigned char b0 = (unsigned char)raw[0], b1 = (unsigned char)raw[1];
        bool le = (b0 == 0xFF && b1 == 0xFE), be = (b0 == 0xFE && b1 == 0xFF);
        if (le || be) {
            std::string ascii;
            ascii.reserve(raw.size() / 2);
            for (size_t i = 2; i + 1 < raw.size(); i += 2) ascii.push_back(le ? raw[i] : raw[i + 1]);
            raw.swap(ascii);
        } else if (raw.size() >= 3 && b0 == 0xEF && b1 == 0xBB && (unsigned char)raw[2] == 0xBF) {
            raw.erase(0, 3);
        }
    }

    palabras.reserve(100000);
    size_t ini = 0;
    while (ini < raw.size()) {
        size_t fin = raw.find('\n', ini);
        if (fin == std::string::npos) fin = raw.size();
        size_t e = fin;
        while (e > ini && (raw[e - 1] == '\r' || raw[e - 1] == ' ' || raw[e - 1] == '\t')) e--;
        if (e > ini) palabras.emplace_back(raw, ini, e - ini);
        ini = fin + 1;
    }
    return palabras;
}

inline bool estaOrdenado(const std::vector<std::string>& v) {
    for (size_t i = 1; i < v.size(); i++)
        if (v[i - 1] > v[i]) return false;
    return true;
}

// Cronometro (steady_clock es monotono; high_resolution_clock puede no serlo)
struct Cronometro {
    std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
    double ms() const {
        return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
    }
};

// ---------------------------------------------------------------
// Estimacion de memoria (aproximada, via sizeof)
// ---------------------------------------------------------------
constexpr size_t OVERHEAD_MALLOC = 16;  // cabecera tipica del asignador por bloque

// Bytes en el heap que usa el buffer de un std::string (0 si cabe en SSO)
inline size_t bytesHeapString(const std::string& s) {
    static const size_t sso = std::string().capacity();
    return s.capacity() > sso ? s.capacity() + 1 + OVERHEAD_MALLOC : 0;
}

inline size_t bytesHeapStrings(const std::vector<std::string>& v) {
    size_t t = 0;
    for (const auto& s : v) t += bytesHeapString(s);
    return t;
}

// vector<string>: n * sizeof(string) + buffers dinamicos de las palabras largas
inline size_t bytesVectorStrings(const std::vector<std::string>& v) {
    return v.size() * sizeof(std::string) + bytesHeapStrings(v);
}

#endif
