#include <climits>
#include <float.h>
#include <cstdlib>

#include "GraphGenerator.h"

#include "AdjacencyList.h"
#include <stack>
#include <unordered_map>

std::shared_ptr<graph::Graph> GraphGenerator::makeCompleteGraph(size_t n) {
  auto graph_ = std::make_shared<graph::AdjacencyList>();

  for (size_t i = 0; i < n; ++i) {
    graph_->addNode(i);
  }

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i; j < n; ++j) {
      if (i != j) {
        float weight = static_cast<float>(rand() % INT_MAX);
        weight = (weight < 0) ? -1 * weight : weight;
        graph_->addEdge(i, j, weight);
        graph_->addEdge(j, i, weight);
      }
    }
  }
  return graph_;
}

std::shared_ptr<graph::Graph> GraphGenerator::makeErdosGraph(size_t n, float oddsOfEdge, bool connected) {
  auto graph_ = std::make_shared<graph::AdjacencyList>();

  for (size_t i = 0; i < n; ++i) {
    graph_->addNode(i);
  }

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i; j < n; ++j) {
      if (i != j) {
        int lucky = rand() % 1000;
        if (lucky < static_cast<int>(oddsOfEdge * 1000)) {
          float weight = static_cast<float>(rand() % 9999) + 1;
          weight = (weight < 0) ? -1 * weight : weight;
          graph_->addEdge(i, j, weight);
          graph_->addEdge(j, i, weight);
        }
      }
    }
  }

  if (connected) {
    //depth search to find unconnected components
    std::stack< size_t > stack;
    std::unordered_map<size_t, bool> visited;
    size_t nComponents = 0;
    for (size_t i = 0; i < n; ++i) {
      visited[i] = false;
    }
    std::vector<std::vector<size_t>>components;
    for (size_t i = 0; i < n; ++i) {
      if (visited[i] == false) {
        //new component
        stack.push(i);
        bool added = false;
        while (!stack.empty()) {
          auto element = stack.top();
          stack.pop();
          visited[element] = true;
          auto adjacency = graph_->getNeighbours(i);
          for (auto v : adjacency) {
            if (!visited[v]) {
              stack.push(v);
              if (components.size() - 1 != nComponents) {
                components.push_back(std::vector<size_t>());
              }
              components[nComponents].push_back(v);
            }
          }
        }
        if (added)
          ++nComponents;

      }
    }
    size_t mergingV = components[0][0];
    for (size_t i = 1; i < nComponents; ++i) {
      auto compVertix = components[i][0];
      float weight = static_cast<float>(rand() % 9999) + 1;
      graph_->addEdge(mergingV, compVertix, weight);
      graph_->addEdge(compVertix, mergingV, weight);
    }
  }

  return graph_;

}