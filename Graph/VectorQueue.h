#ifndef _DCCGRAPH_VECTOR_QUEUE_H_
#define _DCCGRAPH_VECTOR_QUEUE_H_
#include "PriorityQueue.h"
#include <vector>
#include <map>

class VectorQueue : public PriorityQueue < size_t, float > {
public:
  void setup() override{};
private:
  std::map<size_t, float> queue_;
  public:
  VectorQueue();
  ~VectorQueue();
  virtual void add(std::pair<unsigned, float> value) override;
  virtual bool pop(std::pair<unsigned, float> &minValue) override;
  virtual void update(std::pair<unsigned, float> newValue) override;
};

#endif  // _DCCGRAPH_VECTOR_QUEUE_H_
