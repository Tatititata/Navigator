#ifndef PQUEUE_H_
#define PQUEUE_H_
#include <array>
#include <cstring>
#include <iostream>

// PQueue() — создание пустой очереди с приоритетом;
// Push(value) — добавление элемента в очередь;
// Pop() — получение первого элемента очереди с его последующим удалением из
// очереди;

class MinHeap {
 private:
  std::array<size_t, 3>* data_;
  size_t size_;
  size_t capacity_;

  void resize();
  void sift_up();
  void sift_down();

 public:
  MinHeap();
  ~MinHeap();
  MinHeap(const MinHeap&) = delete;
  MinHeap& operator=(const MinHeap&) = delete;
  MinHeap(MinHeap&&) = delete;
  MinHeap& operator=(MinHeap&&) = delete;

  void push(std::array<size_t, 3> value);
  std::array<size_t, 3> pop();
  bool empty() const;
};

#endif