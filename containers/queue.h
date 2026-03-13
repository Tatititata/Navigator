#ifndef QUEUE_H_
#define QUEUE_H_
#include <cstring>
#include <iostream>

// Queue() — создание пустой очереди;
// Push(value) — добавление элемента в очередь;
// Pop() — получение элемента из очереди с его последующим удалением из
// стека/очереди;
// Front() — получение первого элемента из очереди без его
// удаления из очереди;
// Back() — получение последнего элемента из очереди без
// его удаления из очереди.

class Queue {
 private:
  size_t* data_;
  size_t head_;
  size_t tail_;
  size_t capacity_;

  void resize();

 public:
  Queue();
  ~Queue();
  Queue(const Queue&) = delete;
  Queue& operator=(const Queue&) = delete;
  Queue(Queue&&) = delete;
  Queue& operator=(Queue&&) = delete;

  void push(size_t value);
  size_t pop();
  size_t front() const;
  size_t back() const;
  bool empty() const;
};

#endif