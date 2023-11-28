/****
 *
 *
 * copy-and-swap idiom template | Jack Lilhammers
 * https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
 */

#pragma once
#ifndef MINILIST_HPP_
#define MINILIST_HPP_

#include <utility> // swap
#include <cstdlib>   // size_t
#include <exception> // bad_alloc
#include <stdexcept> // runtime_error
#include <string>
#include <compare>   // <=>

template <typename T>
class MiniList
{
private:
  template <typename T>
  struct ListNode
  {
    ListNode<T>* next;
    T data;
  };

  constexpr static std::size_t kMaxSize{ 1000 }; // maximum number of list elements

  std::size_t length_; // number of active elements
  ListNode<T>* head_;  // pointer to first node
  ListNode<T>* tail_;  // pointer to last node


public:
  /* Default Constructor */
  MiniList() noexcept;

  /* Default Destructor */
  ~MiniList();

  /* Capacity */
  bool empty() const noexcept;
  std::size_t size() const noexcept;
  std::size_t max_size() const noexcept;


  /* Swap for copy-and-swap idiom */
  /*
  friend void swap(MiniList<T>& lhs, MiniList<T>& rhs) noexcept {
    // TODO: Implement swap() privately, and/or outside the class. This just
    // worked for now as-is and I got tired of messing with it. The copy and move
    // semantics rely on it.

    using std::swap; // general solution for ensuring correct swap function

    swap(lhs.length_, rhs.length_);
    swap(lhs.head_, rhs.head_);
    swap(lhs.tail_, rhs.tail_);
  }
  */

  /* Copy Semantics */
  MiniList(const MiniList<T>& other) noexcept;
  MiniList<T>& operator=(MiniList<T> other) noexcept;

  /* Move Semantics */
  MiniList(MiniList<T>&& other) noexcept;

  /* Access */
  T front() const;
  T back() const;

  /* Modifiers */
  void push_back(const T& t);
  void push_front(const T& t);
  void pop_back();
  void pop_front();
  void swap(MiniList<T>& lhs, MiniList<T>& rhs) noexcept;
  void clear() noexcept;

  /* Operations */
  void sort() noexcept;
  void unique() noexcept;

  /* Operators */
  friend std::strong_ordering operator<=>(const MiniList<T>& lhs, const MiniList<T>& rhs) {
    auto lhsIt = lhs.begin();
    auto rhsIt = rhs.begin();
    while (lhsIt != lhs.end() && rhsIt != rhs.end()) {
      if (*lhsIt != *rhsIt) {
        return *lhsIt <=> *rhsIt;
      }
      ++lhsIt;
      ++rhsIt;
    }
    return lhs.size() <=> rhs.size();
  }

  /* Iterators */
private:
  class Iterator
  {
  private:
    ListNode<T>* current;

  public:
    Iterator(ListNode<T>* node) noexcept : current(node) {}

    T& operator*() const noexcept
    {
      return current->data;
    }

    Iterator& operator++() noexcept
    {
      current = current->next;
      return *this;
    }
    bool operator!=(const Iterator& other) const noexcept
    {
      return current != other.current;
    }
    bool operator==(const Iterator& other) const noexcept {
      return current == other.current;
    }
  };

public:
  Iterator begin() const noexcept { return Iterator(head_); }
  Iterator end() const noexcept { return Iterator(nullptr); }
};

/* Default Constructor */
template <typename T>
MiniList<T>::MiniList() noexcept : length_(0), head_(nullptr), tail_(nullptr) {}

/* Default Destructor */
template <typename T>
MiniList<T>::~MiniList()
{
  ListNode<T>* current = head_;
  while (current != nullptr)
  {
    ListNode<T>* next = current->next;
    delete current;
    current = next;
  }
}

/* Copy Semantics */
template <typename T>
MiniList<T>::MiniList(const MiniList<T>& other) noexcept : MiniList()
{
  ListNode<T>* current = other.head_;
  while (current != nullptr)
  {
    push_back(current->data);
    current = current->next;
  }
}

template <typename T>
MiniList<T>& MiniList<T>::operator=(MiniList<T> other) noexcept
{
  swap(*this, other);
  return *this;
}

/* Move Semantics */
template <typename T>
MiniList<T>::MiniList(MiniList<T>&& other) noexcept : MiniList<T>()
{
  swap(*this, other);
}

/* Capacity */
template <typename T>
bool MiniList<T>::empty() const noexcept
{
  return (length_ == 0);
}

template <typename T>
std::size_t MiniList<T>::size() const noexcept
{
  return length_;
}

template <typename T>
std::size_t MiniList<T>::max_size() const noexcept
{
  return kMaxSize;
}

/* Access */
template <typename T>
T MiniList<T>::front() const
{
  if (empty())
  {
    throw std::runtime_error("front() attempted to access empty list");
  }
  return head_->data;
}

template <typename T>
T MiniList<T>::back() const
{
  if (empty())
  {
    throw std::runtime_error("back() attempted to access empty list");
  }
  return tail_->data;
}

/* Modifiers */
template <typename T>
void MiniList<T>::push_back(const T& t)
{
  ListNode<T>* newNode;

  try
  {
    newNode = new ListNode<T>;
  }
  catch (const std::bad_alloc& e)
  {
    /* technically, this string concatenation can fail too... */
    throw std::runtime_error("insert() could not allocate new node, error: " + std::string(e.what()));
  }

  newNode->next = nullptr;
  newNode->data = t;

  if (empty())
  {
    head_ = tail_ = newNode;
  }
  else
  {
    tail_->next = newNode;
    tail_ = newNode;
  }

  ++length_;
}

template <typename T>
void MiniList<T>::push_front(const T& t)
{
  ListNode<T>* newNode;

  try
  {
    newNode = new ListNode<T>;
  }
  catch (const std::bad_alloc& e)
  {
    /* technically, this string concatenation can fail too... */
    throw std::runtime_error("push_front() could not allocate new node, error: " + std::string(e.what()));
  }

  newNode->data = t;

  if (empty())
  {
    newNode->next = nullptr;
    head_ = tail_ = newNode;
  }
  else if (size() == 1)
  {
    newNode->next = tail_;
    head_ = newNode;
  }
  else
  {
    newNode->next = head_;
    head_ = newNode;
  }

  ++length_;
}

template <typename T>
void MiniList<T>::pop_back()
{
  if (empty())
  {
    throw std::runtime_error("pop_back attempted to work on empty list");
  }

  if (size() == 1)
  {
    delete head_; // tail_ pointed here too
    head_ = tail_ = nullptr;
    length_ = 0;
  }
  else
  {
    ListNode<T>* newTail = head_;
    while (newTail->next != tail_)
    {
      newTail = newTail->next;
    }
    delete tail_;
    tail_ = newTail;
    tail_->next = nullptr;
    --length_;
  }
}

template <typename T>
void MiniList<T>::pop_front()
{
  if (empty())
  {
    throw std::runtime_error("pop_front attempted to work on empty list");
  }

  if (size() == 1)
  {
    delete head_; // tail_ pointed here too
    head_ = tail_ = nullptr;
    length_ = 0;
  }
  else
  {
    ListNode<T>* newHead = head_->next;
    delete head_;
    head_ = newHead;
    --length_;
  }
}

template <typename T>
void MiniList<T>::swap(MiniList<T>& lhs, MiniList<T>& rhs) noexcept {
  using std::swap; // general solution for ensuring correct swap function

  swap(lhs.length_, rhs.length_);
  swap(lhs.head_, rhs.head_);
  swap(lhs.tail_, rhs.tail_);
}

template <typename T>
void MiniList<T>::clear() noexcept {
  if (empty()) {
    return;
  }
  do {
    pop_front();
  } while (!empty());
}

/***
 * MergeSort for LinkedList
 * Inspired by: Simon Tatham | https://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.html
 * 
 */
template <typename T>
void MiniList<T>::sort() noexcept {
  if (empty() || head_ == tail_) {
    return; // List is empty or has only one element, no need to sort
  }

  ListNode<T>* mergeStart{};
  ListNode<T>* nextSublistStart{};
  ListNode<T>* selectedNode{};
  std::size_t currentSublistSize{};
  std::size_t nextSublistSize{};
  std::size_t mergeSize = 1;
  bool done{};

  do {
    mergeStart = head_;
    head_ = nullptr;
    tail_ = nullptr;
    done = true;

    while (mergeStart) {
      nextSublistStart = mergeStart;
      currentSublistSize = 0;
      for (std::size_t i = 0; i < mergeSize && nextSublistStart; ++i) {
        ++currentSublistSize;
        nextSublistStart = nextSublistStart->next;
      }

      nextSublistSize = mergeSize;
      while (currentSublistSize > 0 || (nextSublistSize > 0 && nextSublistStart)) {
        if (currentSublistSize == 0) {
          selectedNode = nextSublistStart; nextSublistStart = nextSublistStart->next; --nextSublistSize;
        }
        else if (nextSublistSize == 0 || !nextSublistStart) {
          selectedNode = mergeStart; mergeStart = mergeStart->next; --currentSublistSize;
        }
        else if (mergeStart->data <= nextSublistStart->data) {
          selectedNode = mergeStart; mergeStart = mergeStart->next; --currentSublistSize;
        }
        else {
          selectedNode = nextSublistStart; nextSublistStart = nextSublistStart->next; --nextSublistSize;
        }

        if (tail_) {
          tail_->next = selectedNode;
        }
        else {
          head_ = selectedNode;
        }
        tail_ = selectedNode;
        tail_->next = nullptr;
      }

      mergeStart = nextSublistStart;
      done = done && nextSublistStart == nullptr;
    }
    mergeSize *= 2;
  } while (!done);
}

/***
 * unique() finds adjacent duplicate `data` values from `ListNode`.
 * List must be sorted for unique() to work correctly.
 */
template <typename T>
void MiniList<T>::unique() noexcept {
  if (empty() || head_ == tail_) {
    return;
  }

  ListNode<T>* current = head_;
  while (current->next != nullptr) {
    if (current->data == current->next->data) {
      ListNode<T>* toDelete = current->next;
      current->next = current->next->next;
      delete toDelete;
      if (current->next == nullptr) {
        tail_ = current;
      }
    }
    else {
      current = current->next;
    }
  }
}

#endif // MINILIST_HPP_