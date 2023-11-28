
#include "MiniList.hpp"
#include <iostream> // cout
#include <ios>      // boolalpha

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

    std::cout << "\npush_front: 1\n";
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

  std::cout << "Copy and Move Semantics Tests Passed." << std::endl;
}