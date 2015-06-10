#ifndef _DCC_GRAPH_GENERATOR_H_
#define _DCC_GRAPH_GENERATOR_H_

#include "Graph.h"

class GraphGenerator{
  
  public:
  static std::shared_ptr<graph::Graph> makeCompleteGraph(size_t n);
  static std::shared_ptr<graph::Graph> makeErdosGraph(size_t n, float oddsOfEdge, bool connected);
  
};

#endif
