// Nodo.h
#ifndef NODO_H
#define NODO_H

#include <list>
#include <utility> // Para std::pair

struct Nodo {
    int id;
    std::list<std::pair<int, double>> conexiones; // par<id_destino, distancia>
};

#endif // NODO_H
