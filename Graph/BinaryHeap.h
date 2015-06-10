#ifndef _DCC_GRAPH_BINARY_HEAP_H_
#define _DCC_GRAPH_BINARY_HEAP_H_

#include "PriorityQueue.h"
#include <functional>
#include <memory>
#include <queue>


class BinaryHeap : public PriorityQueue < size_t, float > {
  std::unique_ptr<std::vector<std::pair<size_t, float>>> queue_;

  std::function<bool(std::pair<size_t, float>&, std::pair<size_t, float>&)> comp_;

  void setup() override;
  public:
  BinaryHeap();
  virtual ~BinaryHeap() override;
  virtual void add(std::pair<unsigned, float> value) override;
  virtual bool pop(std::pair<unsigned, float>& minValue) override;
  virtual void update(std::pair<unsigned, float> newValue) override;
};


#endif
