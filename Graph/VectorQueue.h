#ifndef _DCCGRAPH_VECTOR_QUEUE_H_
#define _DCCGRAPH_VECTOR_QUEUE_H_
#include "PriorityQueue.h"
#include <unordered_map>
#include <vector>

class VectorQueue : public PriorityQueue < size_t, float > {
  std::vector<std::pair<size_t, float>> queue_;
  public:
  VectorQueue() = default;
  ~VectorQueue() = default;
  virtual void add(std::pair<unsigned, float> value) override;
  virtual bool pop(std::pair<unsigned, float> &minValue) override;
  virtual void update(std::pair<unsigned, float> newValue) override;
  void reserve(size_t n) override;
  void setup() override {};
};

#endif  // _DCCGRAPH_VECTOR_QUEUE_H_
