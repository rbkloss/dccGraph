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
void runDense();
void runSparse();
void runComplete();
bool test();

/*
*
*/
int main(int argc, char** argv) {
#ifndef NDEBUG
  test();
#else
  run();
#endif
  return 0;
}


void run() {
  runSparse();
  runDense();
  runComplete();
}

void runDense() {
  std::vector<std::thread> workers_;
  std::stringstream timeLogBin;
  std::stringstream timeLogFib;
  std::stringstream timeLogVec;


  for (size_t n = 100; n < 9000; n += 1000) {
    printf("n:%u\n", n);
    auto myGraph1 = GraphGenerator::makeErdosGraph(n, 0.70f, true);


    workers_.push_back(std::thread([&timeLogVec, n, &myGraph1]() {

      graph::Dijkstra dijkstraVec(new VectorQueue());
      std::map <size_t, float > distMat1;
      for (int i = 0; i < 1; ++i) {
        auto begin = std::chrono::high_resolution_clock::now();
        auto vecAns = dijkstraVec.getMinPath(myGraph1, 1, distMat1);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        timeLogVec << ms.count() << std::endl;
        distMat1.clear();
      }
    }));

    workers_.push_back(std::thread([&timeLogBin, n, &myGraph1]() {

      graph::Dijkstra dijkstraHeap(new BinaryHeap());
      std::map <size_t, float > distMat1;

      auto begin = std::chrono::high_resolution_clock::now();
      auto binAns = dijkstraHeap.getMinPath(myGraph1, 1, distMat1);
      auto end = std::chrono::high_resolution_clock::now();
      auto elapsed = end - begin;
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
      timeLogBin << ms.count() << std::endl;
      distMat1.clear();
    }));


    workers_.push_back(std::thread([&timeLogFib, n, &myGraph1]() {

      graph::Dijkstra dijkstraFib(new FibonacciHeap());
      std::map <size_t, float > distMat1;
      auto begin = std::chrono::high_resolution_clock::now();
      auto fibAns = dijkstraFib.getMinPath(myGraph1, 1, distMat1);
      auto end = std::chrono::high_resolution_clock::now();
      auto elapsed = end - begin;
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
      timeLogFib << ms.count() << std::endl;
      distMat1.clear();
    }));

    for (auto &thread : workers_) {
      thread.join();
    }
    workers_.clear();
  }
  std::ofstream fTimeLogVec;
  fTimeLogVec.open("dense/timeLogVec.csv");
  std::ofstream fTimeLogBin;
  fTimeLogBin.open("dense/timeLogBin.csv");
  std::ofstream fTimeLogFib;
  fTimeLogFib.open("dense/timeLogFib.csv");

  fTimeLogVec << timeLogVec.str();
  fTimeLogBin << timeLogBin.str();
  fTimeLogFib << timeLogFib.str();


  fTimeLogBin.close();
  fTimeLogVec.close();
  fTimeLogFib.close();
}

void runSparse() {
  std::vector<std::thread> workers_;
  std::stringstream timeLogBin;
  std::stringstream timeLogFib;
  std::stringstream timeLogVec;


  for (size_t n = 100; n < 10000; n += 1000) {
    printf("n:%u\n", n);
    auto myGraph1 = GraphGenerator::makeErdosGraph(n, 0.20f, true);

    workers_.push_back(std::thread([&timeLogVec, n, &myGraph1]() {

      graph::Dijkstra dijkstraVec(new VectorQueue());
      std::map <size_t, float > distMat1;
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

    workers_.push_back(std::thread([&timeLogBin, n, &myGraph1]() {

      graph::Dijkstra dijkstraHeap(new BinaryHeap());
      std::map <size_t, float > distMat1;

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
      std::map <size_t, float > distMat1;
      auto begin = std::chrono::high_resolution_clock::now();
      auto fibAns = dijkstraFib.getMinPath(myGraph1, 1, distMat1);
      auto end = std::chrono::high_resolution_clock::now();
      auto elapsed = end - begin;
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
      timeLogFib << ms.count() << std::endl;
      //assert(binAns == vecAns);
      distMat1.clear();
    }));

    for (auto &thread : workers_) {
      thread.join();
    }
    workers_.clear();
  }
  std::ofstream fTimeLogVec;
  fTimeLogVec.open("sparse/timeLogVec.csv");
  std::ofstream fTimeLogBin;
  fTimeLogBin.open("sparse/timeLogBin.csv");
  std::ofstream fTimeLogFib;
  fTimeLogFib.open("sparse/timeLogFib.csv");

  fTimeLogVec << timeLogVec.str();
  fTimeLogBin << timeLogBin.str();
  fTimeLogFib << timeLogFib.str();


  fTimeLogBin.close();
  fTimeLogVec.close();
  fTimeLogFib.close();
}

void runComplete() {
  std::vector<std::thread> workers_;
  std::stringstream timeLogBin;
  std::stringstream timeLogFib;
  std::stringstream timeLogVec;


  for (size_t n = 100; n < 10000; n += 1000) {
    printf("n:%u\n", n);
    auto myGraph1 = GraphGenerator::makeCompleteGraph(n);

    workers_.push_back(std::thread([&timeLogVec, n, &myGraph1]() {

      graph::Dijkstra dijkstraVec(new VectorQueue());
      std::map <size_t, float > distMat1;
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

    workers_.push_back(std::thread([&timeLogBin, n, &myGraph1]() {

      graph::Dijkstra dijkstraHeap(new BinaryHeap());
      std::map <size_t, float > distMat1;

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
      std::map <size_t, float > distMat1;
      auto begin = std::chrono::high_resolution_clock::now();
      auto fibAns = dijkstraFib.getMinPath(myGraph1, 1, distMat1);
      auto end = std::chrono::high_resolution_clock::now();
      auto elapsed = end - begin;
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
      timeLogFib << ms.count() << std::endl;
      //assert(binAns == vecAns);
      distMat1.clear();
    }));

    for (auto &thread : workers_) {
      thread.join();
    }
    workers_.clear();
  }
  std::ofstream fTimeLogVec;
  fTimeLogVec.open("complete/timeLogVec.csv");
  std::ofstream fTimeLogBin;
  fTimeLogBin.open("complete/timeLogBin.csv");
  std::ofstream fTimeLogFib;
  fTimeLogFib.open("complete/timeLogFib.csv");

  fTimeLogVec << timeLogVec.str();
  fTimeLogBin << timeLogBin.str();
  fTimeLogFib << timeLogFib.str();


  fTimeLogBin.close();
  fTimeLogVec.close();
  fTimeLogFib.close();
}

bool test() {
  std::map<size_t, float> groundTruth = { { 0, 2 }, { 1, 0 }, { 2, 5 }, { 3, 1 } };

  auto adjMat = std::make_shared<graph::AdjacencyMatrix>();
  adjMat->load("inpTest.txt");
  graph::Dijkstra dijkstraVec(new VectorQueue());
  graph::Dijkstra dijkstraFib(new FibonacciHeap());
  graph::Dijkstra dijkstraBin(new BinaryHeap());

  std::map<size_t, float> vecDistMat;
  auto vecAns = dijkstraVec.getMinPath(adjMat, 1, vecDistMat);
  assert(vecDistMat == groundTruth);

  std::map<size_t, float> binDistMat;
  auto binAns = dijkstraBin.getMinPath(adjMat, 1, binDistMat);
  assert(binDistMat == groundTruth);

  std::map<size_t, float> fibDistMat;
  auto fibAns = dijkstraBin.getMinPath(adjMat, 1, fibDistMat);
  assert(fibDistMat == groundTruth);

  std::map<size_t, float> groundTruth2 = { { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 1 } };

  auto adjMat2 = std::make_shared<graph::AdjacencyMatrix>();
  adjMat->load("inpTest2.txt");
  graph::Dijkstra dijkstraVec2(new VectorQueue());
  graph::Dijkstra dijkstraFib2(new FibonacciHeap());
  graph::Dijkstra dijkstraBin2(new BinaryHeap());

  std::map<size_t, float> vecDistMat2;
  auto vecAns2 = dijkstraVec.getMinPath(adjMat, 0, vecDistMat2);
  assert(vecDistMat2 == groundTruth2);

  std::map<size_t, float> binDistMat2;
  auto binAns2 = dijkstraBin.getMinPath(adjMat, 0, binDistMat2);
  assert(binDistMat2 == groundTruth2);

  std::map<size_t, float> fibDistMat2;
  auto fibAns2 = dijkstraBin.getMinPath(adjMat, 0, fibDistMat2);
  assert(fibDistMat2 == groundTruth2);

  return true;
}

