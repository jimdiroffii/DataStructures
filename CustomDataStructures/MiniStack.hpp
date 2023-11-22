/***
 * MiniStack
 *
 * A stack structure template class. 
 * 
 * The objective is to define a statically sized 
 * stack, that models a full stack structure.
 */

#pragma once
#pragma warning(disable : 26455) // ignore default constructor noexcept
#ifndef MINISTACK_H_
#define MINISTACK_H_

#include <memory>    // unique_ptr, make_unique
#include <stdexcept> // runtime_error

template <typename T>
class MiniStack
{
private:
  constexpr static std::size_t kStackSize{10};

  std::size_t length;
  std::size_t counter;
  std::unique_ptr<T[]> elements;

public:
  // Default Constructor
  MiniStack(std::size_t len = 0);

  // Capacity
  bool empty() const noexcept;
  std::size_t size() const noexcept;

  // Modifiers
  void push(const T &t);
  void pop();

  // Access
  T &top() const;
};

template <typename T>
MiniStack<T>::MiniStack(std::size_t len) : length{ len > 0 ? len : kStackSize },
counter{ 0 },
elements{ std::make_unique<T[]>(this->length) } {}

template <typename T>
bool MiniStack<T>::empty() const noexcept
{
  return (counter == 0);
}

template <typename T>
std::size_t MiniStack<T>::size() const noexcept
{
  return counter;
}

template <typename T>
void MiniStack<T>::push(const T &t)
{
  if (counter >= length)
  {
    throw std::runtime_error("Stack overflow in `push`");
  }

  elements[counter++] = t;
}

template <typename T>
T &MiniStack<T>::top() const
{
  if (empty())
  {
    throw std::runtime_error("Stack underflow in `top`");
  }

  return elements[counter - 1];
}

template <typename T>
void MiniStack<T>::pop()
{
  if (empty())
  {
    throw std::runtime_error("Stack underflow in `pop`");
  }

  --counter;
}

#endif // MINISTACK_H_
