#include "FibonacciHeap.h"

void FibonacciHeap::reserve(size_t n){
    //sorry
}

FibonacciHeap::FibonacciHeap() {
  queue_ = new fibHeap();
}
FibonacciHeap::~FibonacciHeap() {
  delete queue_;
}

void FibonacciHeap::add(std::pair<unsigned, float> value) {
  fibHeap::handle_type
    handle = queue_->push(value);
  handleMap_[value.first] = handle;
}

bool FibonacciHeap::pop(std::pair<unsigned, float>& minValue) {
  minValue = queue_->top();
  queue_->pop();
  return queue_->size()>0;
}

void FibonacciHeap::update(std::pair<unsigned, float> newValue) {
  
  auto it = handleMap_.find(newValue.first);
  if (it == handleMap_.end())return;
  
  auto handle = handleMap_.find(newValue.first)->second;
  queue_->increase(handle, newValue);
}

void FibonacciHeap::setup() {

}