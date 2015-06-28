#ifndef _DCC_GRAPH_BINARY_HEAP_H_
#define _DCC_GRAPH_BINARY_HEAP_H_

#include "PriorityQueue.h"
#include <functional>
#include <memory>
#include <unordered_map>

#include <boost/heap/d_ary_heap.hpp>


using boost::heap::d_ary_heap;

typedef std::pair < size_t, float > Key;

struct BinHeapCompare {
  bool operator()(const Key& n1, const Key& n2) const {
    return n1.second > n2.second;
  }
};

typedef d_ary_heap<std::pair<size_t, float>,
  boost::heap::arity<2>, boost::heap::mutable_<true>,
  boost::heap::compare<BinHeapCompare >> Queue_;

class BinaryHeap : public PriorityQueue < size_t, float > {
  Queue_* queue_;

  std::unordered_map < size_t,
    Queue_::handle_type >
    handleMap_;

  std::function<bool(std::pair<size_t, float>&, std::pair<size_t, float>&)> comp_;

  void setup() override;
  public:
  BinaryHeap();
  virtual ~BinaryHeap() override;
  virtual void add(std::pair<unsigned, float> value) override;
  virtual bool pop(std::pair<unsigned, float>& minValue) override;
  virtual void update(std::pair<unsigned, float> newValue) override;
  void reserve(size_t n) override;
};


#endif
