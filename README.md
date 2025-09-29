# HECTOR LUIS MARIÑO FERNANDEZ
## ALU 0100595604
## PRACTICA 1 IA: DFS y BFS

### Descripción

Este proyecto implementa algoritmos de búsqueda no informada (BFS y DFS) para encontrar caminos entre dos vértices de un grafo ponderado no dirigido. El programa lee el grafo desde un fichero de texto en formato compacto (diagonal superior), ejecuta ambas búsquedas y genera un fichero de salida `output.txt` con el detalle de las iteraciones, nodos generados, inspeccionados, camino y coste.

### Estructura de Clases

- **Grafo**: Representa el grafo mediante lista de adyacencia. Permite agregar aristas, obtener el número de vértices y el coste entre dos nodos. Incluye métodos para BFS y DFS detallados.
- **Nodo**: Estructura auxiliar para representar cada vértice y sus conexiones (no es estrictamente necesaria para el funcionamiento principal).
- **Utilidades**: Funciones para leer el grafo desde fichero y declarar las funciones de búsqueda detallada.

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

### Preparar el repositorio para GIT

1. Inicializa el repositorio:
   ```bash
   git init
   ```
2. Añade todos los archivos:
   ```bash
   git add .
   ```
3. Haz tu primer commit:
   ```bash
   git commit -m "Primera versión: BFS y DFS con salida detallada"
   ```
4. (Opcional) Añade el remoto y haz push:
   ```bash
   git remote add origin <URL_DEL_REPO>
   git push -u origin main
   ```