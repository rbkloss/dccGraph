#ifndef _DCCGRAPH_PRIORITY_QUEUE_H_
#define _DCCGRAPH_PRIORITY_QUEUE_H_
#include <utility>
#include <memory>


template<class T, class W> class PriorityQueue {
  public:
  virtual ~PriorityQueue() {}
  virtual void add(std::pair<T, W> value) = 0;
  virtual bool pop(std::pair<T, W>& minValue) = 0;
  virtual void update(std::pair<T, W> newValue) = 0;
  virtual void setup() = 0;

};

#endif  //_DCCGRAPH_PRIORITY_QUEUE_H_
