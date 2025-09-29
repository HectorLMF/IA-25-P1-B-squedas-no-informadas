# HECTOR LUIS MARIÑO FERNANDEZ
## ALU 0100595604
## PRACTICA 1 IA: DFS y BFS

### Descripción

Este proyecto implementa algoritmos de búsqueda no informada (BFS y DFS) para encontrar caminos entre dos vértices de un grafo ponderado no dirigido. El programa lee el grafo desde un fichero de texto en formato compacto (diagonal superior), ejecuta ambas búsquedas y genera un fichero de salida `output.txt` con el detalle de las iteraciones, nodos generados, inspeccionados, camino y coste.

### Estructura de Clases

- **Grafo**: Representa el grafo mediante lista de adyacencia. Permite agregar aristas, obtener el número de vértices y el coste entre dos nodos. Incluye métodos para BFS y DFS detallados.
- **Nodo**: Estructura auxiliar para representar cada vértice y sus conexiones (no es estrictamente necesaria para el funcionamiento principal).
- **Utilidades**: Funciones para leer el grafo desde fichero y declarar las funciones de búsqueda detallada.

### Métodos principales

- **Grafo::agregarArista(int origen, int destino, double costo)**: Añade una arista entre dos vértices con el coste indicado.
- **Grafo::getNumVertices() const**: Devuelve el número de vértices del grafo.
- **Grafo::obtenerCostoArista(int origen, int destino) const**: Devuelve el coste de la arista entre dos vértices, o -1 si no existe.
- **Grafo::imprimirAristas() const**: Muestra por pantalla todas las aristas del grafo.
- **Grafo::busquedaAmplitud(int origen, int destino)**: Realiza búsqueda en amplitud (BFS) y devuelve el camino encontrado como vector de nodos.
- **Grafo::busquedaProfundidad(int origen, int destino)**: Realiza búsqueda en profundidad (DFS) y devuelve el camino encontrado como vector de nodos.
- **busquedaAmplitudDetallada(const Grafo&, int, int)**: Realiza BFS y devuelve un resultado detallado con iteraciones, nodos generados, inspeccionados, camino y coste.
- **busquedaProfundidadDetallada(const Grafo&, int, int)**: Realiza DFS y devuelve un resultado detallado con iteraciones, nodos generados, inspeccionados, camino y coste.
- **leerGrafo(const std::string& nombreArchivo)**: Lee el grafo desde un fichero en formato compacto y lo construye en memoria.

Cada método está documentado en el código fuente y permite modularidad y reutilización para pruebas o ampliaciones.

### Formato del fichero de entrada

El fichero debe tener el siguiente formato:
```
5
1.225
1.000
-1
-1
-1
-1
2.236
1.000
-1
-1
```
Donde el primer número es el número de vértices y el resto son los valores de la diagonal superior de la matriz de distancias (simétrica, -1 si no hay arista).

### Modo de uso

1. Compila el programa:
   ```bash
   g++ -o grafo_program main.cpp Grafo.cpp Utilidades.cpp Nodo.cpp
   ```
2. Ejecuta el programa indicando el fichero de grafo, el nodo origen y el nodo destino (índices desde 0):
   ```bash
   ./grafo_program grafo_test.txt 0 3
   ```
3. El resultado detallado se genera en `output.txt`.
