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
  constexpr static std::size_t kQueueSize{ 10 };

  std::size_t length;
  std::size_t counter;
  std::unique_ptr<T[]> elements;
  
  std::size_t begin; // index of next element to leave queue
  std::size_t end; // index of last element + 1

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
MiniQueue<T>::MiniQueue(std::size_t len) : length{ len > 0 ? len : kQueueSize },
counter{ 0 },
elements{ std::make_unique<T[]>(this->length) },
begin{ 0 },
end{ 0 } {}

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
  
  // loop back around to the start of the queue after reaching the end
  if (end >= length) {
    end = 0;
  }

  elements[end++] = t;
  ++counter;
}

template <typename T>
T& MiniQueue<T>::front() const
{
  if (empty())
  {
    throw std::runtime_error("Queue underflow in `front`");
  }

  return elements[begin];
}

template <typename T>
T& MiniQueue<T>::back() const
{
  if (empty())
  {
    throw std::runtime_error("Queue underflow in `back`");
  }

  // if the last element is at the end of the structure, wrap the
  // index access to the end of the structure
  if (end - 1 < 0) {
    return elements[length - 1];
  }

  return elements[end - 1];
}

template <typename T>
void MiniQueue<T>::pop()
{
  if (empty())
  {
    throw std::runtime_error("Queue underflow in `pop`");
  }

  // there is only a single element left, reset the queue
  if ((begin + 1 == end) || (begin + 1 >= length && end == 0)) {
    counter = begin = end = 0;
    return;
  }

  // wrap begin back around to the beginning
  if (begin + 1 >= length) {
    begin = 0;
  }
  else {
    begin += 1;
  }

  --counter;
}

#endif // MINIQUEUE_HPP_
