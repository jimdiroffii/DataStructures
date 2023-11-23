/***
 * MiniQueue
 *
 * A queue structure template class.
 *
 * The objective is to define a statically sized
 * queue, that models a full queue structure.
 * 
 * The queue is more complicated than a stack in that it requires 
 * a circular buffer management of the front and back
 * of the queue. As long as the queue elements_ are 
 * not maxed out, then the queue can wrap around the 
 * last index, and the queue moves in a windowed fashion.
 */

#pragma once
#pragma warning(disable : 26455) // ignore default constructor noexcept
#ifndef MINIQUEUE_HPP_
#define MINIQUEUE_HPP_

#include <algorithm> // copy, move
#include <memory>    // unique_ptr, make_unique
#include <stdexcept> // runtime_error

template <typename T>
class MiniQueue
{
private:
  constexpr static std::size_t kQueueSize{ 10 };

  std::size_t length_;    // total capacity or size of queue
  std::unique_ptr<T[]> elements_;
  
  std::size_t counter_;   // number of elements
  std::size_t begin_;     // index of next element to leave queue
  std::size_t end_;       // index of last element + 1

public:
  /* Default Constructor */
  MiniQueue(std::size_t len = 0);

  /* Capacity */
  bool empty() const noexcept;
  std::size_t size() const noexcept;

  /* Modifiers */
  void push(const T& t);
  void pop();

  /* Access */
  T& front() const;
  T& back() const;

  /* Copy */
  MiniQueue(const MiniQueue& other);
  MiniQueue& operator=(const MiniQueue& other);

  /* Move */
  MiniQueue(MiniQueue&& other) noexcept;
  MiniQueue& operator=(MiniQueue&& other) noexcept;
};

/* if a length has been input, use that for sizing the queue */
template <typename T>
MiniQueue<T>::MiniQueue(std::size_t length) : 
  length_{ length > 0 ? length : kQueueSize },
  elements_{ std::make_unique<T[]>(this->length_) },
  counter_{ 0 },
  begin_{ 0 },
  end_{ 0 } {}

template <typename T>
bool MiniQueue<T>::empty() const noexcept
{
  return (counter_ == 0);
}

template <typename T>
std::size_t MiniQueue<T>::size() const noexcept
{
  return counter_;
}

template <typename T>
void MiniQueue<T>::push(const T& t)
{
  if (counter_ >= length_)
  {
    throw std::runtime_error("Queue overflow in `push`");
  }
  
  /* loop back around to the start of the queue after reaching the end */
  if (end_ >= length_) {
    end_ = 0;
  }

  elements_[end_++] = t;
  ++counter_;
}

template <typename T>
T& MiniQueue<T>::front() const
{
  if (empty())
  {
    throw std::runtime_error("Queue underflow in `front`");
  }

  return elements_[begin_];
}

template <typename T>
T& MiniQueue<T>::back() const
{
  if (empty())
  {
    throw std::runtime_error("Queue underflow in `back`");
  }

  /* if the last element is at the end of the structure, wrap the
     index access to the end of the structure */
  if (end_ == 0) {
    return elements_[length_ - 1];
  }

  return elements_[end_ - 1];
}

template <typename T>
void MiniQueue<T>::pop()
{
  if (empty())
  {
    throw std::runtime_error("Queue underflow in `pop`");
  }

  /* there is only a single element left, reset the queue */
  if ((begin_ + 1 == end_) || (begin_ + 1 >= length_ && end_ == 0)) {
    counter_ = begin_ = end_ = 0;
    return;
  }

  /* wrap begin back around to the beginning */
  if (begin_ + 1 >= length_) {
    begin_ = 0;
  }
  else {
    begin_ += 1;
  }

  --counter_;
}

/* Copy constructor */
template <typename T>
MiniQueue<T>::MiniQueue(const MiniQueue& other) :
  length_(other.length_),
  elements_(std::make_unique<T[]>(other.length_)),
  counter_(other.counter_),
  begin_(other.begin_),
  end_(other.end_)
{
  std::copy(&other.elements_[0], &other.elements_[other.length_], &elements_[0]);
}

/* Copy assignment operator */
template <typename T>
MiniQueue<T>& MiniQueue<T>::operator=(const MiniQueue& other)
{
  if (this != &other) {
    elements_ = std::make_unique<T[]>(other.length_);
    std::copy(&other.elements_[0], &other.elements_[other.length_], &elements_[0]);
    length_ = other.length_;
    counter_ = other.counter_;
    begin_ = other.begin_;
    end_ = other.end_;
  }
  return *this;
}

/* Move constructor */
template <typename T>
MiniQueue<T>::MiniQueue(MiniQueue&& other) noexcept :
  length_(other.length_),
  elements_(std::move(other.elements_)),
  counter_(other.counter_),
  begin_(other.begin_),
  end_(other.end_)
{
  other.length_ = 0;
  other.counter_ = 0;
  other.begin_ = 0;
  other.end_ = 0;
}

/* Move assignment operator */
template <typename T>
MiniQueue<T>& MiniQueue<T>::operator=(MiniQueue&& other) noexcept
{
  if (this != &other) {
    length_ = other.length_;
    elements_ = std::move(other.elements_);
    counter_ = other.counter_;
    begin_ = other.begin_;
    end_ = other.end_;

    other.length_ = 0;
    other.counter_ = 0;
    other.begin_ = 0;
    other.end_ = 0;
  }
  return *this;
}

#endif // MINIQUEUE_HPP_
