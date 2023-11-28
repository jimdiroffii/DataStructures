
#include "MiniList.hpp"
#include <iostream> // cout
#include <ios>      // boolalpha
#include <compare>  // <=>
#include <vector>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

/* Test functions */
#include <cassert>
template <typename T>
void printList(const MiniList<T>& list);
void testMiniListCopyAndMoveSemantics();
template <typename T>
void fillListFromVector(MiniList<T>& list, const std::vector<T>& vec);
template <typename T>
bool compareListWithVector(const MiniList<T>& list, const std::vector<T>& vec);
void testSort();


template <typename T>
void testMiniListComparison();

int main()
{
#ifdef _DEBUG
  // Enable memory leak detection
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  std::cout << std::boolalpha;
  std::cout << "MiniList Testing!\n";

  /* Constructors */
  MiniList<int> miniList{};

  /* Capacity */
  {
    std::cout << "empty: " << miniList.empty() << '\n';
    std::cout << "size: " << miniList.size() << '\n';
    std::cout << "max size: " << miniList.max_size() << '\n';
  }

  /* Access & Modification */
  {
    std::cout << "\nEmpty list\n";
    printList(miniList);

    int a = 1;
    miniList.push_front(a);
    miniList.push_front(a);
    miniList.push_front(a);

    std::cout << "\npush_front x3: 1\n";
    printList(miniList);

    miniList.unique();

    printList(miniList);

    int b = 2;
    miniList.push_front(b);

    std::cout << "push_front: 2\n";
    printList(miniList);

    int c = 3;
    miniList.push_back(c);

    std::cout << "push_back: 3\n";
    printList(miniList);

    int d = 4;
    miniList.push_back(d);

    std::cout << "push_back: 4\n";
    printList(miniList);

    miniList.sort();

    printList(miniList);

    miniList.pop_back();

    std::cout << "\npop_back:\n";
    printList(miniList);

    miniList.pop_front();

    std::cout << "pop_front:\n";
    printList(miniList);

    miniList.pop_back();

    std::cout << "pop_back:\n";
    printList(miniList);

    std::cout << "pop_front:\n";
    miniList.pop_front();
    printList(miniList);

    testMiniListCopyAndMoveSemantics();
    testMiniListComparison<int>();
    testSort();
  }

#ifdef _DEBUG
  // Report any memory leaks
  _CrtDumpMemoryLeaks();
#endif
}

template <typename T>
void printList(const MiniList<T>& list)
{
  // Helper function to print list contents for debugging
  for (auto current = list.begin(); current != list.end(); ++current)
  {
    std::cout << *current << " ";
  }
  std::cout << std::endl;
}

void testMiniListCopyAndMoveSemantics()
{
  // Create a list and populate it
  MiniList<int> originalList;
  for (int i = 1; i <= 5; ++i)
  {
    originalList.push_back(i);
  }

  // Copy constructor test
  MiniList<int> copiedList(originalList);
  assert(copiedList.size() == originalList.size()); // Sizes should be equal
  // Optionally, check the content of the list
  printList(copiedList);

  // Copy assignment test
  MiniList<int> assignedList;
  assignedList = originalList;
  assert(assignedList.size() == originalList.size()); // Sizes should be equal
  // Optionally, check the content of the list
  printList(assignedList);

  // Move constructor test
  MiniList<int> movedList(std::move(originalList));
  assert(movedList.size() == 5); // Moved list should have original size
  assert(originalList.empty());  // Original list should be empty after move
  // Optionally, check the content of the list
  printList(movedList);

  // Move assignment test
  MiniList<int> moveAssignedList;
  moveAssignedList = std::move(movedList);
  assert(moveAssignedList.size() == 5); // List should have size 5 after move
  assert(movedList.empty());            // Moved-from list should be empty
  // Optionally, check the content of the list
  printList(moveAssignedList);

  copiedList.clear();
  assert(copiedList.empty());

  assignedList.clear();
  assert(assignedList.empty());

  moveAssignedList.clear();
  assert(moveAssignedList.empty());

  std::cout << "Copy and Move Semantics Tests Passed." << std::endl;
}

template<typename T>
void testMiniListComparison() {
  // Test scenarios
  MiniList<T> list1;
  MiniList<T> list2;
  MiniList<T> list3;

  // Populate lists with some data
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  list2.push_back(1);
  list2.push_back(2);
  list2.push_back(3);

  list3.push_back(4);
  list3.push_back(5);
  list3.push_back(6);

  // Test for equality
  assert((list1 <=> list2) == std::strong_ordering::equal);

  // Test for less than
  assert((list1 <=> list3) == std::strong_ordering::less);

  // Test for greater than
  assert((list3 <=> list1) == std::strong_ordering::greater);

  // Test empty lists
  MiniList<T> emptyList1;
  MiniList<T> emptyList2;

  assert((emptyList1 <=> emptyList2) == std::strong_ordering::equal);

  // Test a list with different sizes
  MiniList<T> list4;
  list4.push_back(1);
  list4.push_back(2);

  assert((list1 <=> list4) == std::strong_ordering::greater);

  printList(list1);
  printList(list2);
  printList(list3);
  printList(list4);

  std::cout << "Ordering Semantics Tests Passed." << std::endl;
}

// Helper function to fill a MiniList from a vector
template <typename T>
void fillListFromVector(MiniList<T>& list, const std::vector<T>& vec) {
  list.clear();
  for (const auto& item : vec) {
    list.push_back(item);
  }
}

// Helper function to compare MiniList with a vector
template <typename T>
bool compareListWithVector(const MiniList<T>& list, const std::vector<T>& vec) {
  auto it = list.begin();
  for (const auto& item : vec) {
    if (it == list.end() || *it != item) {
      return false;
    }
    ++it;
  }
  return it == list.end();
}

void testSort() {
  MiniList<int> list;

  // Test sorting an empty list
  list.sort();
  assert(list.empty());

  // Test sorting a list with one element
  list.push_back(1);
  list.sort();
  assert(compareListWithVector(list, { 1 }));

  // Test sorting a list with elements in reverse order
  fillListFromVector(list, { 3, 2, 1 });
  list.sort();
  assert(compareListWithVector(list, { 1, 2, 3 }));

  // Test sorting an already sorted list
  fillListFromVector(list, { 1, 2, 3 });
  list.sort();
  assert(compareListWithVector(list, { 1, 2, 3 }));

  // Test sorting a list with random elements
  fillListFromVector(list, { 5, 1, 4, 3, 2 });
  list.sort();
  assert(compareListWithVector(list, { 1, 2, 3, 4, 5 }));

  // Test sorting a list with duplicate elements
  fillListFromVector(list, { 3, 1, 2, 3, 1 });
  printList(list);
  list.sort();
  printList(list);
  assert(compareListWithVector(list, { 1, 1, 2, 3, 3 }));

  std::cout << "All sort tests passed." << std::endl;
}