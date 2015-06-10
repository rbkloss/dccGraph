#ifndef _DCC_GRAPH_FIBONACCI_HEAP_H_
#define _DCC_GRAPH_FIBONACCI_HEAP_H_

#include "PriorityQueue.h"
#include <map>
typedef std::pair<size_t, float>  Key;
class FibonacciHeap : public PriorityQueue < size_t, float > {
  public:
  struct FibonacciNode {
    Key key_;
    bool mark_;//whether node has lost a child since the last time it was made the child of another node
    FibonacciNode *up_;
    FibonacciNode *left_;
    FibonacciNode *right_;
    FibonacciNode *down_;
    int degree_;//number of children
    FibonacciNode(Key key, void* payload) :key_(key), mark_(false), up_(nullptr), left_(nullptr), right_(nullptr), down_(nullptr), degree_(0){}
  };// FibonacciNode
  std::map<size_t, FibonacciNode*> map_node_;
  int n_;
  FibonacciNode*min_;

  FibonacciHeap();
  virtual ~FibonacciHeap() override;
  virtual void add(Key value) override;
  virtual bool pop(Key& minValue) override;
  virtual void update(Key newValue) override;
  virtual void setup() override;

  private:
  void deleteHeap(FibonacciNode* x);
  FibonacciNode* insert(Key k);
  void insert(FibonacciNode* n);
  FibonacciNode* extractMin();

  void consolidate();
  void heapLink(FibonacciNode* y, FibonacciNode* x);

  void decreaseKey(FibonacciNode* x, Key k);
  void cut(FibonacciNode* x, FibonacciNode* y);
  void cascadingCut(FibonacciNode* x);

  static FibonacciHeap* unionFibHeap(FibonacciHeap* h1, FibonacciHeap* h2);
  void removeNode(FibonacciNode* x);


}; // FibonacciHeap

#endif
