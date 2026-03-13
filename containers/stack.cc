#include "stack.h"

Stack::Stack() : data_(new size_t[2]), size_(0), capacity_(2) {}
Stack::~Stack() { delete[] data_; }

void Stack::resize() {
  capacity_ *= 2;
  size_t* new_data = new size_t[capacity_];
  std::memmove(new_data, data_, sizeof(size_t) * size_);
  delete[] data_;
  data_ = new_data;
}

void Stack::push(size_t value) {
  if (size_ >= capacity_) {
    resize();
  }
  data_[size_++] = value;
}

size_t Stack::pop() {
  if (empty()) {
    throw std::out_of_range("Stack is empty");
  }
  size_t value = data_[size_ - 1];
  --size_;
  return value;
}

bool Stack::empty() const { return size_ == 0; }

size_t Stack::top() const {
  if (empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return data_[size_ - 1];
}
