$CC = gcc
$CFLAGS = -std=c++11 
$LFLAGS = -c -std=c++11

$HEADERS = Graph.h AdjacencyList.h AdjacencyMatrix.h
$SOURCES = AdjacencyList.cc AdjacencyMatrix.cc

all: adjacencyList.o adjacencyMatrix.o main.c
	$(CC)  $(CFLAGS) adjacencyList.o adjacencyMatrix.o main.c -o graph.exe
adjacencyList.o: Graph.h AdjacencyList.h AdjacencyList.cc
	$(CC)  $(LFLAGS) AdjacencyList.cc
adjacencyMatrix.o: Graph.h AdjacencyMatrix.h AdjacencyMatrix.cc
	$(CC)  $(LFLAGS) AdjacencyMatrix.cc