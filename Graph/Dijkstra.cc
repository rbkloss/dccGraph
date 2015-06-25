#include "Dijkstra.h"

namespace graph {
  Dijkstra::Dijkstra(PriorityQueue<size_t, float>* queue) {
    if (queue == nullptr) {
      queue_ = new VectorQueue();
    } else {
      queue_ = queue;
    }
  }

  Dijkstra::~Dijkstra() {
    delete queue_;
  }

  std::map<size_t, size_t> Dijkstra::getMinPath(
    const std::shared_ptr<graph::Graph>& graph,
    const size_t source, std::map<size_t, float> &distances) {
    //generates the distance matrix
    std::map<size_t, size_t> predecessorsVector;
    for (size_t i = 0; i < graph->getSize(); ++i) {
      distances[i] = FLT_MAX;
      predecessorsVector[i] = -1;
    }
    distances[source] = 0;
    for (size_t i = 0; i < graph->getSize(); ++i) {
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
        float weightToNode = 0.0f;
        std::for_each(distances.begin(), distances.end(),
          [&weightToNode, &currentNode](std::pair<size_t, float> el) {if (el.first == currentNode) weightToNode = el.second; });
        float oldWeight = 0.0f;
        std::for_each(distances.begin(), distances.end(),
          [&oldWeight, &node](std::pair<size_t, float> el) {if (el.first == node) oldWeight = el.second; });
        float newWeight = edgeWeight + weightToNode;
        if (newWeight < oldWeight) {
          //update
          queue_->update(std::make_pair((node), newWeight));
          distances[node] = newWeight;
          predecessorsVector[node] = currentNode;
        }
      }
      ++visited;
    } while (visited < graph->getSize());
    return predecessorsVector;
  }
}