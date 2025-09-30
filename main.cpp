#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "Grafo.h"
#include "Utilidades.h"

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "Uso: " << argv[0] << " <fichero_grafo> <origen> <destino>" << std::endl;
        return 1;
    }

    std::string ficheroGrafo = argv[1];
    int origen = std::stoi(argv[2]);
    int destino = std::stoi(argv[3]);

    Grafo grafo = leerGrafo(ficheroGrafo);

    if (origen < 0 || origen >= grafo.getNumVertices() || destino < 0 || destino >= grafo.getNumVertices()) {
        std::cerr << "Vértices fuera de rango. Deben estar entre 0 y " << grafo.getNumVertices() - 1 << "." << std::endl;
        return 1;
    }

    grafo.imprimirAristas();
    cout << "-------------------------------------------------------------"<< endl;

    std::vector<int> caminoBFS = grafo.busquedaAmplitud(origen, destino);
    std::vector<int> caminoDFS = grafo.busquedaProfundidad(origen, destino);

    // Imprimir camino BFS
    std::cout << "Camino BFS: ";
    for (int nodo : caminoBFS) {
        std::cout << nodo << "->";
    }
    std::cout << std::endl;

    // Calcular y mostrar costo total de BFS
    double costoTotalBFS = 0;
    for (size_t i = 0; i < caminoBFS.size() - 1; ++i) {
        costoTotalBFS += grafo.obtenerCostoArista(caminoBFS[i], caminoBFS[i + 1]);
    }
    std::cout << "Costo total BFS: " << costoTotalBFS << std::endl;
    cout << "-------------------------------------------------------------"<< endl;

    // Imprimir camino DFS
    std::cout << "Camino DFS: ";
    for (int nodo : caminoDFS) {
        std::cout << nodo << "->";
    }
    std::cout << std::endl;

    // Calcular y mostrar costo total de DFS
    double costoTotalDFS = 0;
    for (size_t i = 0; i < caminoDFS.size() - 1; ++i) {
        costoTotalDFS += grafo.obtenerCostoArista(caminoDFS[i], caminoDFS[i + 1]);
    }
    std::cout << "Costo total DFS: " << costoTotalDFS << std::endl;

    ResultadoBusqueda resultadoBFS = busquedaAmplitudDetallada(grafo, origen, destino);
    ResultadoBusqueda resultadoDFS = busquedaProfundidadDetallada(grafo, origen, destino);
    std::ofstream fout("output.txt");
    fout << "---------------------------------------------\n";
    fout << "Número de nodos del grafo: " << grafo.getNumVertices() << std::endl;
    int aristas = 0;
    const auto& listaAdy = grafo.getListaAdyacencia();
    for (int i = 0; i < grafo.getNumVertices(); ++i)
        for (const auto& v : listaAdy[i])
            if (i < v.first) ++aristas;
    fout << "Número de aristas del grafo: " << aristas << std::endl;
    fout << "Vértice origen: " << (origen+1) << std::endl;
    fout << "Vértice destino: " << (destino+1) << std::endl;
    fout << "---------------------------------------------\n";
    // BFS
    fout << "BÚSQUEDA EN AMPLITUD (BFS)" << std::endl;
    fout << "Nodo aleatorio elegido en la primera iteración (por nodoAleatorio): " << (resultadoBFS.nodoAleatorioUsado+1) << std::endl;
    for (size_t i = 0; i < resultadoBFS.iteraciones.size(); ++i) {
        fout << "Iteración " << (i+1) << std::endl;
        fout << "Nodos generados: ";
        bool first = true;
        for (int n : resultadoBFS.iteraciones[i].generados) {
            if (!first) fout << ", ";
            fout << (n);
            first = false;
        }
        fout << std::endl;
        fout << "Nodos inspeccionados: ";
        if (resultadoBFS.iteraciones[i].inspeccionados.empty()) fout << "-";
        else {
            first = true;
            for (int n : resultadoBFS.iteraciones[i].inspeccionados) {
                if (!first) fout << ", ";
                fout << (n);
                first = false;
            }
        }
        fout << std::endl << "---------------------------------------------\n";
    }
    fout << "Camino: ";
    for (size_t i = 0; i < resultadoBFS.camino.size(); ++i) {
        fout << (resultadoBFS.camino[i]+1);
        if (i+1 < resultadoBFS.camino.size()) fout << " - ";
    }
    fout << std::endl << "---------------------------------------------\n";
    fout << "Costo: " << std::fixed << std::setprecision(2) << resultadoBFS.costo << std::endl;
    fout << "---------------------------------------------\n";
    // DFS
    fout << "BÚSQUEDA EN PROFUNDIDAD (DFS)" << std::endl;
    fout << "Nodo aleatorio elegido en la primera iteración (por nodoAleatorio): " << (resultadoDFS.nodoAleatorioUsado+1) << std::endl;
    for (size_t i = 0; i < resultadoDFS.iteraciones.size(); ++i) {
        fout << "Iteración " << (i+1) << std::endl;
        fout << "Nodos generados: ";
        bool first = true;
        for (int n : resultadoDFS.iteraciones[i].generados) {
            if (!first) fout << ", ";
            fout << (n);
            first = false;
        }
        fout << std::endl;
        fout << "Nodos inspeccionados: ";
        if (resultadoDFS.iteraciones[i].inspeccionados.empty()) fout << "-";
        else {
            first = true;
            for (int n : resultadoDFS.iteraciones[i].inspeccionados) {
                if (!first) fout << ", ";
                fout << (n);
                first = false;
            }
        }
        fout << std::endl << "---------------------------------------------\n";
    }
    fout << "Camino: ";
    for (size_t i = 0; i < resultadoDFS.camino.size(); ++i) {
        fout << (resultadoDFS.camino[i]+1);
        if (i+1 < resultadoDFS.camino.size()) fout << " - ";
    }
    fout << std::endl << "---------------------------------------------\n";
    fout << "Costo: " << std::fixed << std::setprecision(2) << resultadoDFS.costo << std::endl;
    fout << "---------------------------------------------\n";
    fout.close();

    std::cout << "Resultado detallado guardado en output.txt" << std::endl;

    return 0;
}
