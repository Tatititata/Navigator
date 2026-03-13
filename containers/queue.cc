#include "queue.h"

Queue::Queue() : data_(new size_t[2]), head_(0), tail_(0), capacity_(2) {}
Queue::~Queue() { delete[] data_; }

bool Queue::empty() const { return head_ == tail_; }

void Queue::push(size_t value) {
  if (tail_ == capacity_) {
    resize();
  }
  data_[tail_++] = value;
}

void Queue::resize() {
  if (head_) {
    std::memmove(data_, data_ + head_, sizeof(size_t) * (tail_ - head_));
    tail_ -= head_;
    head_ = 0;
  } else {
    capacity_ *= 2;
    size_t* new_data = new size_t[capacity_];
    std::memmove(new_data, data_, sizeof(size_t) * (tail_ - head_));
    delete[] data_;
    data_ = new_data;
  }
}

size_t Queue::pop() {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  size_t value = data_[head_++];
  return value;
}

size_t Queue::front() const {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  return data_[head_];
}

size_t Queue::back() const {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  size_t idx = tail_ - 1;
  return data_[idx];
}