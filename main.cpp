/*
 * File:   main.cpp
 * Author: ricardo
 *
 * Created on March 12, 2015, 7:59 PM
 */

#include <cstdlib>

#include "dccGraph.h"
#include <memory>
#include <sstream>
/*
 *
 */
int main(int argc, char** argv) {
  auto myGraph1 = GraphGenerator::makeCompleteGraph(10);
  graph::Dijkstra dijkstra(new FibonacciHeap());
  std::map <size_t, float > distMat1;
  auto ans = dijkstra.getMinPath(myGraph1, 1, distMat1);

  auto myGraph2 = GraphGenerator::makeErdosGraph(10, 0.4f, true);
  std::map <size_t, float > distMat2;
  ans = dijkstra.getMinPath(myGraph1, 1, distMat2);

  auto adjMat = std::make_shared<graph::AdjacencyMatrix>();
  adjMat->load("inpTest.txt");
  auto adjList = std::make_shared<graph::AdjacencyList>();  
  adjList->convert(adjMat);
  adjList->save("adjList.txt");

  return 0;
}

