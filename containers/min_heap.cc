#include "min_heap.h"

MinHeap::MinHeap()
    : data_(new std::array<size_t, 3>[2]), size_(0), capacity_(2) {}
MinHeap::~MinHeap() { delete[] data_; }

void MinHeap::resize() {
  capacity_ *= 2;
  std::array<size_t, 3>* new_data = new std::array<size_t, 3>[capacity_];
  std::memmove(new_data, data_, sizeof(std::array<size_t, 3>) * size_);
  delete[] data_;
  data_ = new_data;
}

void MinHeap::push(std::array<size_t, 3> value) {
  if (size_ >= capacity_) {
    resize();
  }
  data_[size_++] = value;
  if (size_ > 1) {
    sift_up();
  }
}

std::array<size_t, 3> MinHeap::pop() {
  if (empty()) {
    throw std::out_of_range("Priority queue is empty");
  }
  std::array<size_t, 3> value = std::move(data_[0]);
  --size_;
  if (size_ == 0) {
    return value;
  }
  data_[0] = std::move(data_[size_]);
  sift_down();
  return value;
}

bool MinHeap::empty() const { return size_ == 0; }

void MinHeap::sift_up() {
  size_t child = size_ - 1;
  size_t parent = (child - 1) / 2;
  while (child > 0 && data_[child] < data_[parent]) {
    std::swap(data_[child], data_[parent]);
    child = parent;
    parent = (child - 1) / 2;
  }
}

void MinHeap::sift_down() {
  size_t i = 0;
  bool result = false;
  while (!result) {
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;
    size_t smallest = i;
    if (left < size_) {
      if (data_[left] < data_[smallest]) {
        smallest = left;
      }
      if (right < size_ && data_[right] < data_[smallest]) {
        smallest = right;
      }
    }
    if (smallest == i) {
      result = true;
    } else {
      std::swap(data_[i], data_[smallest]);
      i = smallest;
    }
  }
}