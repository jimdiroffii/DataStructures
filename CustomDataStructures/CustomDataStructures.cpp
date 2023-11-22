/***
 * Data Structures and Testing
 * Jim Diroff II
 *
 * Driver code file | main
 */

#include "MiniStack.h"
#include <iostream>

void stackTest();

int main()
{
  stackTest();
}

void stackTest()
{
  constexpr int n{27};

  // Constructor test
  MiniStack<int> ministack_A{1};
  MiniStack<int> ministack_B{2};

  // Empty test
  std::cout << "Empty\n";
  std::cout << "Expected: 1, Actual: " << ministack_A.empty() << '\n';
  std::cout << "Expected: 1, Actual: " << ministack_B.empty() << '\n';
  std::cout << "Expected: 0, Actual: " << ministack_A.size() << '\n';
  std::cout << "Expected: 0, Actual: " << ministack_B.size() << '\n';

  // Push test
  std::cout << "Push\n";
  ministack_A.push(n);
  ministack_B.push(n + 1);
  ministack_B.push(n + 2);
  std::cout << "Expected: 0, Actual: " << ministack_A.empty() << '\n';
  std::cout << "Expected: 0, Actual: " << ministack_B.empty() << '\n';
  std::cout << "Expected: 1, Actual: " << ministack_A.size() << '\n';
  std::cout << "Expected: 2, Actual: " << ministack_B.size() << '\n';

  // Top-access test
  std::cout << "Top\n";
  std::cout << "Expected: 27, Actual: " << ministack_A.top() << '\n';
  std::cout << "Expected: 29, Actual: " << ministack_B.top() << '\n';

  // Pop test
  std::cout << "Pop\n";
  ministack_A.pop();
  ministack_B.pop();
  ministack_B.pop();
  std::cout << "Expected: 1, Actual: " << ministack_A.empty() << '\n';
  std::cout << "Expected: 1, Actual: " << ministack_B.empty() << '\n';
  std::cout << "Expected: 0, Actual: " << ministack_A.size() << '\n';
  std::cout << "Expected: 0, Actual: " << ministack_B.size() << '\n';

  // Exception test
  try
  {
    while (true)
    {
      ministack_A.push(0);
    }
  }
  catch (const std::runtime_error &e)
  {
    std::cout << e.what() << '\n';
  }

  try
  {
    while (true)
    {
      ministack_A.pop();
    }
  }
  catch (const std::runtime_error &e)
  {
    std::cout << e.what() << '\n';
  }

  try
  {
    ministack_A.top();
  }
  catch (const std::runtime_error &e)
  {
    std::cout << e.what() << '\n';
  }
}