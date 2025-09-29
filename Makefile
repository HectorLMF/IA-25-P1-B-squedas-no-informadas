CXX = g++
CXXFLAGS = -Wall -std=c++11
OBJS = main.o Grafo.o Utilidades.o Nodo.o
TARGET = grafo_program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp Grafo.h Utilidades.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Grafo.o: Grafo.cpp Grafo.h Nodo.h
	$(CXX) $(CXXFLAGS) -c Grafo.cpp

Utilidades.o: Utilidades.cpp Utilidades.h Grafo.h
	$(CXX) $(CXXFLAGS) -c Utilidades.cpp

Nodo.o: Nodo.cpp Nodo.h
	$(CXX) $(CXXFLAGS) -c Nodo.cpp

clean:
	rm -f *.o $(TARGET)
