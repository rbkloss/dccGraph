#include <algorithm>


#include "BinaryHeap.h"

void BinaryHeap::setup() {
}

BinaryHeap::BinaryHeap() {
  queue_ = new Queue_;
  
  //comp_ = [](std::pair<size_t, float>& i, std::pair<size_t, float>&j)->bool {
  //  return i.second > j.second;
  //};
}

BinaryHeap::~BinaryHeap(){
  delete queue_;
}

void BinaryHeap::add(std::pair<unsigned, float> value) {
  Queue_::handle_type
    handle = queue_->push(value);
  handleMap_[value.first] = handle;
}

bool BinaryHeap::pop(std::pair<unsigned, float>& minValue) {
  minValue = queue_->top();
  queue_->pop();
    
  return queue_->empty();
}

void BinaryHeap::update(std::pair<unsigned, float> newValue) {
  auto it = handleMap_.find(newValue.first);
  if (it == handleMap_.end())return;
  auto handle = handleMap_.find(newValue.first)->second;
  queue_->increase(handle, newValue);
}

void BinaryHeap::reserve(size_t n){
  queue_->reserve(n);
}