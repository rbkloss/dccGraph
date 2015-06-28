#include "Dijkstra.h"
#include <algorithm>

namespace graph {
  Dijkstra::Dijkstra(PriorityQueue<size_t, float>* queue) {
    if (queue == nullptr) {
      throw new std::exception("NullPtr Exception\n");
    }
    queue_ = queue;
  }

  Dijkstra::~Dijkstra() {
    delete queue_;
    queue_ = nullptr;
  }

  std::unordered_map<size_t, size_t> Dijkstra::getMinPath(
    const std::shared_ptr<graph::Graph>& graph,
    const size_t source, std::unordered_map<size_t, float> &distances) {
    //generates the distance matrix
    std::unordered_map<size_t, size_t> predecessorsVector;
    for (size_t i = 0; i < graph->getSize().first; ++i) {
      distances[i] = FLT_MAX;
      predecessorsVector[i] = -1;
    }
    distances[source] = 0;
    queue_->reserve(graph->getSize().first);
    for (size_t i = 0; i < graph->getSize().first; ++i) {
      queue_->add(std::make_pair(i, distances[i]));
    }
    queue_->setup();

    //starts from the source 
    //until no
    size_t currentNode = 0;
    bool status = false;
    size_t visited = 0;
    do {
      std::pair<size_t, float> minValue;
      status = queue_->pop(minValue);
      currentNode = minValue.first;
      //update all weights
      auto neighbours = graph->getNeighbours(currentNode);
      for (auto node : neighbours) {
        float edgeWeight = graph->getEdge(currentNode, node);
        float weightToNode = distances[currentNode];
        float newWeight = weightToNode + edgeWeight;

        float oldWeight = distances[node];        
        if (newWeight < oldWeight) {
          //update
          queue_->update(std::make_pair((node), newWeight));
          distances[node] = newWeight;
          predecessorsVector[node] = currentNode;
        }
      }
      ++visited;
    } while (visited < graph->getSize().first);
    return predecessorsVector;
  }
}