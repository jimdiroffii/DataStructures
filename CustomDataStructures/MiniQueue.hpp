/***
 * MiniQueue
 *
 * A queue structure template class.
 *
 * The objective is to define a statically sized
 * queue, that models a full queue structure.
 * 
 * The queue is more complicated in that it requires 
 * a circular buffer management of the front and back
 * of the queue. As long as the queue elements are 
 * not maxed out, then the queue can wrap around the 
 * last index, and the queue moves in a windowed fashion.
 */

#pragma once
#pragma warning(disable : 26455) // ignore default constructor noexcept
#ifndef MINIQUEUE_HPP_
#define MINIQUEUE_HPP_

#include <memory>    // unique_ptr, make_unique
#include <stdexcept> // runtime_error

template <typename T>
class MiniQueue
{
private:
  constexpr static std::size_t kStackSize{ 10 };

  std::size_t length;
  std::size_t counter;
  std::unique_ptr<T[]> elements;

public:
  // Default Constructor
  MiniQueue(std::size_t len = 0);

  // Capacity
  bool empty() const noexcept;
  std::size_t size() const noexcept;

  // Modifiers
  void push(const T& t);
  void pop();

  // Access
  T& front() const;
  T& back() const;
};

template <typename T>
MiniQueue<T>::MiniQueue(std::size_t len) : length{ len > 0 ? len : kStackSize },
counter{ 0 },
elements{ std::make_unique<T[]>(this->length) } {}

template <typename T>
bool MiniQueue<T>::empty() const noexcept
{
  return (counter == 0);
}

template <typename T>
std::size_t MiniQueue<T>::size() const noexcept
{
  return counter;
}

template <typename T>
void MiniQueue<T>::push(const T& t)
{
  if (counter >= length)
  {
    throw std::runtime_error("Queue overflow in `push`");
  }

  elements[counter++] = t;
}

template <typename T>
T& MiniQueue<T>::front() const
{
  if (empty())
  {
    throw std::runtime_error("Queue underflow in `front`");
  }

  return elements[0];
}

template <typename T>
T& MiniQueue<T>::back() const
{
  if (empty())
  {
    throw std::runtime_error("Queue underflow in `back`");
  }

  return elements[counter - 1];
}

template <typename T>
void MiniQueue<T>::pop()
{
  if (empty())
  {
    throw std::runtime_error("Queue underflow in `pop`");
  }

  --counter;
}

#endif // MINIQUEUE_HPP_
