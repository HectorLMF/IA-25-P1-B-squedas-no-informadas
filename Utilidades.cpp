#include "Utilidades.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

int nodoAleatorio(int numVertices) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, numVertices - 1);
    return dis(gen);
}

Grafo leerGrafo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo " << nombreArchivo << std::endl;
        exit(1);
    }

    int n;
    archivo >> n;
    Grafo grafo(n);

    // Leer solo la diagonal superior compacta (formato enunciado)
    std::vector<std::vector<double>> matriz(n, std::vector<double>(n, -1));
    for (int i = 0; i < n; ++i) {
        matriz[i][i] = 0; // d(i,i) = 0
    }
    for (int i = 0, k = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j, ++k) {
            double distancia;
            archivo >> distancia;
            matriz[i][j] = distancia;
            matriz[j][i] = distancia;
        }
    }
    // Agregar aristas
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (matriz[i][j] != -1) {
                grafo.agregarArista(i, j, matriz[i][j]);
            }
        }
    }
    archivo.close();
    return grafo;
}
