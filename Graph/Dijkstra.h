#ifndef _DCCGRAPH_DIJKSTRA_H_
#define _DCCGRAPH_DIJKSTRA_H_

#include "./PriorityQueue.h"
#include "Graph.h"
#include <algorithm>
#include <map>
#include "VectorQueue.h"

namespace graph {
  class Dijkstra {
    PriorityQueue<size_t, float>* queue_;
    public:
    explicit Dijkstra(PriorityQueue<size_t, float>* queue = new VectorQueue());
    virtual ~Dijkstra();
    std::map<size_t, size_t> getMinPath(const std::shared_ptr<graph::Graph> &graph,
      const size_t source, std::map<size_t, float> &distances);
  };
}
#endif // _DCCGRAPH_DIJKSTRA_H_

