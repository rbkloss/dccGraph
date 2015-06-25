#ifndef _DCC_GRAPH_FIBONACCI_HEAP_H_
#define _DCC_GRAPH_FIBONACCI_HEAP_H_

#include "PriorityQueue.h"
#include <map>
#include <boost/heap/fibonacci_heap.hpp>



using boost::heap::fibonacci_heap;
typedef std::pair<size_t, float>  Key;

struct FibonacciCompare {
  bool operator()(const Key& n1, const Key& n2) const {
    return n1.second > n2.second;
  }
};

typedef fibonacci_heap<Key, boost::heap::compare<FibonacciCompare>> fibHeap;


class FibonacciHeap : public PriorityQueue < size_t, float > {
  public:
  fibHeap *queue_;
  std::map < size_t,
    fibHeap::handle_type >
    handleMap_;

  FibonacciHeap();
  virtual ~FibonacciHeap() override;
  virtual void add(Key value) override;
  virtual bool pop(Key& minValue) override;
  virtual void update(Key newValue) override;
  virtual void setup() override;

}; // FibonacciHeap

#endif
