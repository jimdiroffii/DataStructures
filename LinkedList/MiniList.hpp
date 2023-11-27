#pragma once
#ifndef MINILIST_HPP_
#define MINILIST_HPP_

#include <cstdlib> // size_t
#include <stdexcept> // runtime_error
#include <string>

template <typename T>
struct ListNode {
  ListNode<T>* next;
  T data;
};

template <typename T>
class MiniList
{
private:
  constexpr static std::size_t kMaxSize{ 1000 }; // maximum number of list elements

  std::size_t length_; // number of active elements
  ListNode<T>* head_;   // pointer to first node
  ListNode<T>* tail_;   // pointer to last node

public:
  /* Default Constructor */
  MiniList();

  /* Capacity */
  bool empty() const noexcept;
  std::size_t size() const noexcept;
  std::size_t max_size() const noexcept;

  /* Access */
  T front() const;
  T back() const;

  /* Modifiers */
  void push_back(const T& t);
  void push_front(const T& t);
  void pop_back();
  void pop_front();
};

/* Default Constructor */
template <typename T>
MiniList<T>::MiniList() : length_(0), head_(nullptr), tail_(nullptr) {}

/* Capacity */
template <typename T>
bool MiniList<T>::empty() const noexcept {
  return (length_ == 0);
}

template <typename T>
std::size_t MiniList<T>::size() const noexcept {
  return length_;
}

template <typename T>
std::size_t MiniList<T>::max_size() const noexcept {
  return kMaxSize;
}

/* Access */
template <typename T>
T MiniList<T>::front() const {
  if (empty() || head_ == nullptr) {
    return NULL;
  }
  return head_->data;
}

template <typename T>
T MiniList<T>::back() const {
  if (empty() || tail_ == nullptr) {
    return NULL;
  }
  return tail_->data;
}

/* Modifiers */
template <typename T>
void MiniList<T>::push_back(const T& t) {
  ListNode<T>* newNode;

  try {
    newNode = new ListNode<T>;
  }
  catch (const std::bad_alloc& e) {
    /* technically, this string concatenation can fail too... */
    throw std::runtime_error("insert() could not allocate new node, error: " + std::string(e.what()));
  }

  newNode->next = nullptr;
  newNode->data = t;

  if (empty()) {
    head_ = tail_ = newNode;
  }
  else {
    tail_->next = newNode;
    tail_ = newNode;
  }

  ++length_;
}

template <typename T>
void MiniList<T>::push_front(const T& t) {
  ListNode<T>* newNode;

  try {
    newNode = new ListNode<T>;
  }
  catch (const std::bad_alloc& e) {
    /* technically, this string concatenation can fail too... */
    throw std::runtime_error("push_front() could not allocate new node, error: " + std::string(e.what()));
  }
  
  newNode->data = t;

  if (empty()) {
    newNode->next = nullptr;
    head_ = tail_ = newNode;
  }
  else if (size() == 1) {
    newNode->next = tail_;
    head_ = newNode;
  }
  else {
    newNode->next = head_;
    head_ = newNode;
  }

  ++length_;
}

template <typename T>
void MiniList<T>::pop_back() {
  if (empty()) {
    throw std::runtime_error("pop_back attempted to work on empty list");
  }

  // TODO: might need to handle destruction of underlying data before pop
  if (size() == 1) {
    head_ = tail_ = nullptr;
    length_ = 0;
  }
  else {
    ListNode<T>* ptr = head_;
    while (ptr->next != tail_) {
      ptr = ptr->next;
    }
    tail_ = ptr;
    ptr->next = nullptr;
    --length_;
  }
}

template <typename T>
void MiniList<T>::pop_front() {
  if (empty()) {
    throw std::runtime_error("pop_front attempted to work on empty list");
  }

  if (size() == 1) {
    head_ = tail_ = nullptr;
    length_ = 0;
  }
  else {
    head_ = head_->next;
    --length_;
  }
}

#endif //MINILIST_HPP_