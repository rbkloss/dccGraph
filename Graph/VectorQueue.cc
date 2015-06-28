#include "VectorQueue.h"

void VectorQueue::reserve(size_t n) {
  queue_.reserve(n);
}

void VectorQueue::add(std::pair<unsigned, float> value) {
  queue_.push_back(value);
}

bool VectorQueue::pop(std::pair<size_t, float>& minValue) {
  if (queue_.empty())return false;
  auto min = queue_.begin();
  auto it = queue_.begin();
  for (; it != queue_.end(); ++it) {
    if (min->second >= it->second) {
      min = it;
    }
  }
  minValue = (*min);
  queue_[min->first] = std::make_pair(min->first, FLT_MAX);
  return true;
}

void VectorQueue::update(std::pair<unsigned, float> newValue) {
  queue_[newValue.first] = newValue;
}
