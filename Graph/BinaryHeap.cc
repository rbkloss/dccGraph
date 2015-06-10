#include <algorithm>
#include <cassert>

#include "BinaryHeap.h"

void BinaryHeap::setup() {
  std::sort(queue_->begin(), queue_->end(), comp_);
  std::make_heap(queue_->begin(), queue_->end(), comp_);
  assert(std::is_heap(queue_->begin(), queue_->end(), comp_));
}

BinaryHeap::BinaryHeap() {
  queue_ = std::make_unique<std::vector<std::pair<size_t, float>>>();
  comp_ = [](std::pair<size_t, float>& i, std::pair<size_t, float>&j)->bool {
    return i.second > j.second;
  };
}

BinaryHeap::~BinaryHeap() {}

void BinaryHeap::add(std::pair<unsigned, float> value) {
  queue_->push_back(value);
}

bool BinaryHeap::pop(std::pair<unsigned, float>& minValue) {
  minValue = queue_->front();
  std::pop_heap(queue_->begin(), queue_->end(), comp_);
  queue_->pop_back();
  assert(std::is_heap(queue_->begin(), queue_->end(), comp_));
  return queue_->empty();
}

void BinaryHeap::update(std::pair<unsigned, float> newValue) {
  std::push_heap(queue_->begin(), queue_->end(), comp_);
  assert(std::is_heap(queue_->begin(), queue_->end(), comp_));
}
