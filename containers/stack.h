#ifndef STACK_H_
#define STACK_H_
#include <cstring>
#include <iostream>

class Stack {
 private:
  size_t* data_;
  size_t size_;
  size_t capacity_;

  void resize();

 public:
  Stack();
  ~Stack();
  Stack(const Stack&) = delete;
  Stack& operator=(const Stack&) = delete;
  Stack(Stack&&) = delete;
  Stack& operator=(Stack&&) = delete;

  void push(size_t value);
  size_t pop();
  size_t top() const;
  bool empty() const;
  size_t size() const { return size_; }
};

#endif

// stack() — создание пустого стека;
// push(value) — добавление элемента в стек;
// pop() — получение элемента из стека с его последующим удалением из стека;
// top() — получение элемента из стека без его удаления из стека;