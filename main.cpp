/*
 * File:   main.cpp
 * Author: ricardo
 *
 * Created on March 12, 2015, 7:59 PM
 */

#include <cstdlib>
#include <memory>
#include <fstream>
#include <chrono>
#include <thread>
#include <sstream>
#include <cassert>

#include "dccGraph.h"
void run();
void runExperiment(unsigned begin, unsigned N, unsigned step, const std::string &prefix, float p = 1.0f);

bool test();

/*
*
*/
int main(int argc, char** argv) {
#ifndef NDEBUG
  test();
#endif

  run();
  return 0;
}


void run() {
  unsigned N = 10000;
  unsigned begin = 500;
  unsigned step = 1000;

  //runExperiment(begin, N, step, "sparse/", 0.001f);
  //runExperiment(begin, N, step, "dense/", 0.15f);
  runExperiment(begin, N, step, "complete/");

}

void runExperiment(unsigned from, unsigned to, unsigned step,
  const std::string& prefix, float p) {
  std::vector<std::thread> workers_;
  std::stringstream timeLogBin;
  std::stringstream timeLogFib;
  std::stringstream timeLogVec;

  std::shared_ptr<graph::Graph> myGraph1;
  for (size_t n = from; n < to; n += step) {
    printf("n:%u\n", n);
    if (p >= 1.0f) {
      myGraph1 = GraphGenerator::makeCompleteGraph(n);
    } else {
      myGraph1 = GraphGenerator::makeErdosGraph(n, p, true);
    }
    auto sz = myGraph1->getSize();
    printf("V=%u, E=%u\n\n", sz.first, sz.second);

    workers_.push_back(std::thread([&timeLogBin, n, &myGraph1]() {

      graph::Dijkstra dijkstraHeap(new BinaryHeap());
      std::unordered_map <size_t, float > distMat1;

      auto begin = std::chrono::high_resolution_clock::now();
      auto binAns = dijkstraHeap.getMinPath(myGraph1, 1, distMat1);
      auto end = std::chrono::high_resolution_clock::now();
      auto elapsed = end - begin;
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
      timeLogBin << ms.count() << std::endl;
      //assert(binAns == vecAns);
      distMat1.clear();
    }));

    workers_.push_back(std::thread([&timeLogFib, n, &myGraph1]() {

      graph::Dijkstra dijkstraFib(new FibonacciHeap());
      std::unordered_map <size_t, float > distMat1;
      auto begin = std::chrono::high_resolution_clock::now();
      auto fibAns = dijkstraFib.getMinPath(myGraph1, 1, distMat1);
      auto end = std::chrono::high_resolution_clock::now();
      auto elapsed = end - begin;
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
      timeLogFib << ms.count() << std::endl;
      //assert(binAns == vecAns);
      distMat1.clear();
    }));

    workers_.push_back(std::thread([&timeLogVec, n, &myGraph1]() {

      graph::Dijkstra dijkstraVec(new VectorQueue());
      std::unordered_map <size_t, float > distMat1;
      for (int i = 0; i < 1; ++i) {
        auto begin = std::chrono::high_resolution_clock::now();
        auto vecAns = dijkstraVec.getMinPath(myGraph1, 1, distMat1);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        timeLogVec << ms.count() << std::endl;
        //assert(binAns == vecAns);
        distMat1.clear();
      }
    }));


   

    for (auto &thread : workers_) {
      thread.join();
    }
    workers_.clear();
    myGraph1.reset();
  }
  std::ofstream fTimeLogVec;
  fTimeLogVec.open(prefix + "timeLogVec.csv");
  std::ofstream fTimeLogBin;
  fTimeLogBin.open(prefix + "timeLogBin.csv");
  std::ofstream fTimeLogFib;
  fTimeLogFib.open(prefix + "timeLogFib.csv");

  fTimeLogVec << timeLogVec.str();
  fTimeLogBin << timeLogBin.str();
  fTimeLogFib << timeLogFib.str();


  fTimeLogBin.close();
  fTimeLogVec.close();
  fTimeLogFib.close();
}

bool test() {
  std::unordered_map<size_t, float> groundTruth = { { 0, 2 }, { 1, 0 }, { 2, 5 }, { 3, 1 } };

  auto adjMat = std::make_shared<graph::AdjacencyMatrix>();
  adjMat->load("inpTest.txt");
  graph::Dijkstra dijkstraVec(new VectorQueue());
  graph::Dijkstra dijkstraFib(new FibonacciHeap());
  graph::Dijkstra dijkstraBin(new BinaryHeap());

  std::unordered_map<size_t, float> vecDistMat;
  auto vecAns = dijkstraVec.getMinPath(adjMat, 1, vecDistMat);
  assert(vecDistMat == groundTruth);

  std::unordered_map<size_t, float> binDistMat;
  auto binAns = dijkstraBin.getMinPath(adjMat, 1, binDistMat);
  assert(binDistMat == groundTruth);

  std::unordered_map<size_t, float> fibDistMat;
  auto fibAns = dijkstraBin.getMinPath(adjMat, 1, fibDistMat);
  assert(fibDistMat == groundTruth);

  std::unordered_map<size_t, float> groundTruth2 = { { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 1 } };

  auto adjMat2 = std::make_shared<graph::AdjacencyMatrix>();
  adjMat->load("inpTest2.txt");
  graph::Dijkstra dijkstraVec2(new VectorQueue());
  graph::Dijkstra dijkstraFib2(new FibonacciHeap());
  graph::Dijkstra dijkstraBin2(new BinaryHeap());

  std::unordered_map<size_t, float> vecDistMat2;
  auto vecAns2 = dijkstraVec.getMinPath(adjMat, 0, vecDistMat2);
  assert(vecDistMat2 == groundTruth2);

  std::unordered_map<size_t, float> binDistMat2;
  auto binAns2 = dijkstraBin.getMinPath(adjMat, 0, binDistMat2);
  assert(binDistMat2 == groundTruth2);

  std::unordered_map<size_t, float> fibDistMat2;
  auto fibAns2 = dijkstraBin.getMinPath(adjMat, 0, fibDistMat2);
  assert(fibDistMat2 == groundTruth2);

  return true;
}

