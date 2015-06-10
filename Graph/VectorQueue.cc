#include "VectorQueue.h"
VectorQueue::VectorQueue() {}

VectorQueue::~VectorQueue() {}

void VectorQueue::add(std::pair<unsigned, float> value) {
  queue_[value.first] = value.second;
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
  minValue = static_cast<std::pair<size_t, float>>(*min);
  queue_.erase(min);  
  return true;
}

void VectorQueue::update(std::pair<unsigned, float> newValue) {
  for (auto &value : queue_) {
    auto it = queue_.find(newValue.first);
    if (it != queue_.end()) {
      if (newValue.first == value.first) {
        queue_[newValue.first] = newValue.second;
        break;
      }
    }
  }
}