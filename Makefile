CXX      = g++
CXXFLAGS = -O2 -std=c++17 -Wall -Wextra

all: practica generar_dataset

practica: main.cpp quicksort.cpp heapsort.cpp avltree.cpp utils.h
	$(CXX) $(CXXFLAGS) main.cpp quicksort.cpp heapsort.cpp avltree.cpp -o practica

generar_dataset: generar_dataset.cpp
	$(CXX) $(CXXFLAGS) generar_dataset.cpp -o generar_dataset

clean:
	rm -f practica generar_dataset *.exe
