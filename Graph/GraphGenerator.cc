#include "GraphGenerator.h"

#include <stack>
#include <unordered_map>
#include <random>

#include "AdjacencyMatrix.h"


std::shared_ptr<graph::Graph> GraphGenerator::makeCompleteGraph(size_t n) {
  auto graph_ = std::make_shared<graph::AdjacencyMatrix>();
  graph_->resize(n);
  std::uniform_real_distribution<float> weightDistribution(1.0f, 100000.0f);
  std::default_random_engine generator;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      float weight = (weightDistribution(generator));
      weight = (weight < 0) ? -1 * weight : weight;
      graph_->addEdge(i, j, weight);
      graph_->addEdge(j, i, weight);
    }
  }
  return graph_;
}

std::shared_ptr<graph::Graph> GraphGenerator::makeErdosGraph(size_t n, float oddsOfEdge, bool connected) {
  auto graph_ = std::make_shared<graph::AdjacencyMatrix>();

  graph_->resize(n);
  std::default_random_engine generator;
  std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
  std::uniform_real_distribution<float> weightDistribution(1.0f, 100000.0f);

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      float lucky = distribution(generator);
      if (lucky < oddsOfEdge) {
        float weight = (weightDistribution(generator));
        weight = (weight < 0) ? -1 * weight : weight;
        graph_->addEdge(i, j, weight);
        graph_->addEdge(j, i, weight);
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
      float weight = (weightDistribution(generator));
      graph_->addEdge(mergingV, compVertix, weight);
      graph_->addEdge(compVertix, mergingV, weight);
    }
  }

  return graph_;

}