#include "Grafo.h"
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
#include <set>
#include <fstream>
#include <random>
#include "Utilidades.h"
using namespace std;



// Constructor que inicializa el grafo con n vértices
Grafo::Grafo(int n) : numVertices(n), listaAdyacencia(n) {}

// Función para agregar una arista con un costo entre dos vértices
void Grafo::agregarArista(int origen, int destino, double costo) {
    listaAdyacencia[origen].push_back({destino, costo});
    listaAdyacencia[destino].push_back({origen, costo});  // Grafo no dirigido
}

int Grafo::getNumVertices() const {
    return numVertices;
}

// Búsqueda en Amplitud (BFS)
std::vector<int> Grafo::busquedaAmplitud(int origen, int destino) {
    std::vector<bool> visitado(numVertices, false);
    std::vector<int> predecesor(numVertices, -1);
    std::queue<int> cola;
    int nodo_inicial = nodoAleatorio(numVertices);
    std::cout << "[BFS] Nodo aleatorio elegido en la primera iteración (por nodoAleatorio): " << nodo_inicial+1 << std::endl;
    visitado[nodo_inicial] = true;
    cola.push(nodo_inicial);
    bool primera_iteracion = true;
    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();
        std::cout << "[BFS] Evaluando nodo: " << actual+1 << std::endl;
        std::vector<int> hijos;
        for (const auto& vecino : listaAdyacencia[actual]) {
            int v = vecino.first;
            if (!visitado[v]) {
                hijos.push_back(v);
            }
        }
        if (!hijos.empty()) {
            std::cout << "[BFS] Hijos de " << actual+1 << ": ";
            for (size_t i = 0; i < hijos.size(); ++i) {
                std::cout << hijos[i]+1;
                if (i+1 < hijos.size()) std::cout << ", ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "[BFS] El nodo " << actual+1 << " no tiene hijos nuevos." << std::endl;
        }
        if (primera_iteracion) {
            primera_iteracion = false;
            if (actual == destino) break;
            if (!visitado[origen]) {
                visitado[origen] = true;
                predecesor[origen] = actual;
                cola.push(origen);
            }
            continue;
        }
        if (actual == destino) {
            break;
        }
        for (const auto& vecino : listaAdyacencia[actual]) {
            int v = vecino.first;
            if (!visitado[v]) {
                visitado[v] = true;
                predecesor[v] = actual;
                cola.push(v);
            }
        }
    }
    std::vector<int> camino;
    for (int v = destino; v != -1; v = predecesor[v]) {
        camino.push_back(v);
    }
    std::reverse(camino.begin(), camino.end());
    return camino;
}

// Búsqueda en Profundidad (DFS)
std::vector<int> Grafo::busquedaProfundidad(int origen, int destino) {
    std::vector<int> camino;
    std::vector<bool> visitado(numVertices, false);
    std::vector<int> predecesor(numVertices, -1);
    int nodo_inicial = nodoAleatorio(numVertices);
    std::cout << "[DFS] Nodo aleatorio elegido en la primera iteración (por nodoAleatorio): " << nodo_inicial+1 << std::endl;
    bool primera_iteracion = true;
    std::stack<int> pila;
    pila.push(nodo_inicial);
    while (!pila.empty()) {
        int actual = pila.top();
        pila.pop();
        std::cout << "[DFS] Evaluando nodo: " << actual+1 << std::endl;
        std::vector<int> hijos;
        for (const auto& vecino : listaAdyacencia[actual]) {
            int v = vecino.first;
            if (!visitado[v]) {
                hijos.push_back(v);
            }
        }
        if (!hijos.empty()) {
            std::cout << "[DFS] Hijos de " << actual+1 << ": ";
            for (size_t i = 0; i < hijos.size(); ++i) {
                std::cout << hijos[i]+1;
                if (i+1 < hijos.size()) std::cout << ", ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "[DFS] El nodo " << actual+1 << " no tiene hijos nuevos." << std::endl;
        }
        if (primera_iteracion) {
            primera_iteracion = false;
            if (actual == destino) break;
            if (!visitado[origen]) {
                predecesor[origen] = actual;
                pila.push(origen);
            }
            visitado[actual] = true;
            continue;
        }
        if (!visitado[actual]) {
            visitado[actual] = true;
            if (actual == destino) break;
            for (const auto& vecino : listaAdyacencia[actual]) {
                int v = vecino.first;
                if (!visitado[v]) {
                    predecesor[v] = actual;
                    pila.push(v);
                }
            }
        }
    }
    if (predecesor[destino] == -1 && nodo_inicial != destino) {
        return camino;
    }
    for (int v = destino; v != -1; v = predecesor[v]) {
        camino.push_back(v);
    }
    std::reverse(camino.begin(), camino.end());
    return camino;
}

void Grafo::dfsRecursivo(int actual, int destino, std::vector<bool>& visitado, std::vector<int>& predecesor) {
    visitado[actual] = true;

    if (actual == destino) {
        return;
    }

    for (const auto& vecino : listaAdyacencia[actual]) {
        int v = vecino.first;
        if (!visitado[v]) {
            predecesor[v] = actual;
            dfsRecursivo(v, destino, visitado, predecesor);
        }
    }
}

void Grafo::imprimirAristas() const {
    for (int i = 0; i < numVertices; ++i) {
        for (const auto& vecino : listaAdyacencia[i]) {
            int destino = vecino.first;
            double costo = vecino.second;
            if (i < destino) {  // Evitar imprimir la misma arista dos veces en un grafo no dirigido
                std::cout << "Arista: " << i << " - " << destino << " (Costo: " << costo << ")" << std::endl;
            }
        }
    }
}


double Grafo::obtenerCostoArista(int origen, int destino) const {
    for (const auto& vecino : listaAdyacencia[origen]) {
        if (vecino.first == destino) {
            return vecino.second;  // Retorna el costo de la arista
        }
    }
    return -1;  // Retorna -1 si no hay arista
}

ResultadoBusqueda busquedaAmplitudDetallada(const Grafo& grafo, int origen, int destino) {
    int n = grafo.getNumVertices();
    std::vector<bool> visitado(n, false);
    std::vector<int> predecesor(n, -1);
    std::queue<int> cola;
    std::vector<IteracionBusqueda> iteraciones;
    std::set<int> generados, inspeccionados;
    const auto& listaAdyacencia = grafo.getListaAdyacencia();
    // Elegir aleatoriamente uno de los hijos del nodo origen
    std::vector<int> hijos;
    for (const auto& vecino : listaAdyacencia[origen]) {
        hijos.push_back(vecino.first);
    }
    int nodoAleatorioUsado = origen;
    if (!hijos.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, hijos.size() - 1);
        nodoAleatorioUsado = hijos[dis(gen)];
    }
    visitado[nodoAleatorioUsado] = true;
    cola.push(nodoAleatorioUsado);
    generados.insert(nodoAleatorioUsado);
    iteraciones.push_back({generados, {}});
    bool primera_iteracion = true;
    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();
        inspeccionados.insert(actual);
        IteracionBusqueda it = iteraciones.back();
        it.inspeccionados = inspeccionados;
        iteraciones.back() = it;
        if (primera_iteracion) {
            primera_iteracion = false;
            if (actual == destino) break;
            if (!visitado[origen]) {
                visitado[origen] = true;
                predecesor[origen] = actual;
                cola.push(origen);
                generados.insert(origen);
            }
            continue;
        }
        for (const auto& vecino : listaAdyacencia[actual]) {
            int v = vecino.first;
            if (!visitado[v]) {
                visitado[v] = true;
                predecesor[v] = actual;
                cola.push(v);
                generados.insert(v);
            }
        }
        iteraciones.push_back({generados, inspeccionados});
        if (actual == destino) break;
    }
    std::vector<int> camino;
    for (int v = destino; v != -1; v = predecesor[v]) camino.push_back(v);
    std::reverse(camino.begin(), camino.end());
    double costo = 0;
    if (!camino.empty()) {
        for (size_t i = 0; i + 1 < camino.size(); ++i)
            costo += grafo.obtenerCostoArista(camino[i], camino[i + 1]);
    }
    return {camino, costo, iteraciones, nodoAleatorioUsado};
}

ResultadoBusqueda busquedaProfundidadDetallada(const Grafo& grafo, int origen, int destino) {
    int n = grafo.getNumVertices();
    std::vector<bool> visitado(n, false);
    std::vector<int> predecesor(n, -1);
    std::vector<IteracionBusqueda> iteraciones;
    std::set<int> generados, inspeccionados;
    const auto& listaAdyacencia = grafo.getListaAdyacencia();
    // Elegir aleatoriamente uno de los hijos del nodo origen
    std::vector<int> hijos;
    for (const auto& vecino : listaAdyacencia[origen]) {
        hijos.push_back(vecino.first);
    }
    int nodoAleatorioUsado = origen;
    if (!hijos.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, hijos.size() - 1);
        nodoAleatorioUsado = hijos[dis(gen)];
    }
    std::stack<int> pila;
    pila.push(nodoAleatorioUsado);
    generados.insert(nodoAleatorioUsado);
    iteraciones.push_back({generados, {}});
    bool found = false;
    bool primera_iteracion = true;
    while (!pila.empty() && !found) {
        int actual = pila.top(); pila.pop();
        if (!visitado[actual]) {
            visitado[actual] = true;
            inspeccionados.insert(actual);
            IteracionBusqueda it = iteraciones.back();
            it.inspeccionados = inspeccionados;
            iteraciones.back() = it;
            if (primera_iteracion) {
                primera_iteracion = false;
                if (actual == destino) { found = true; break; }
                if (!visitado[origen]) {
                    predecesor[origen] = actual;
                    pila.push(origen);
                    generados.insert(origen);
                }
                continue;
            }
            for (const auto& vecino : listaAdyacencia[actual]) {
                int v = vecino.first;
                if (!visitado[v]) {
                    predecesor[v] = actual;
                    pila.push(v);
                    generados.insert(v);
                    if (v == destino) { found = true; break; }
                }
            }
            iteraciones.push_back({generados, inspeccionados});
        }
    }
    std::vector<int> camino;
    if (predecesor[destino] != -1 || origen == destino) {
        for (int v = destino; v != -1; v = predecesor[v]) camino.push_back(v);
        std::reverse(camino.begin(), camino.end());
    }
    double costo = 0;
    if (!camino.empty()) {
        for (size_t i = 0; i + 1 < camino.size(); ++i)
            costo += grafo.obtenerCostoArista(camino[i], camino[i + 1]);
    }
    return {camino, costo, iteraciones, nodoAleatorioUsado};
}
