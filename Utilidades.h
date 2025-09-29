#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "Grafo.h"
#include <string>

Grafo leerGrafo(const std::string& nombreArchivo);
ResultadoBusqueda busquedaAmplitudDetallada(const Grafo& grafo, int origen, int destino);
ResultadoBusqueda busquedaProfundidadDetallada(const Grafo& grafo, int origen, int destino);

#endif
