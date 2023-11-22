/***
 * Data Structures and Testing
 * Jim Diroff II
 *
 * Driver code file | main
 */

#include "MiniStack.hpp"
#include <iostream>
#include <chrono> // high_resolution_clock
#include <stack>
#include <cstdint>

// void stackTest();

void miniStackPushPops(const std::size_t iterations);
void stackPushPops(const std::size_t iterations);

int main()
{
  constexpr std::size_t kIter{1000000000};
  std::chrono::nanoseconds elapsedTimeMiniStack{};
  std::chrono::nanoseconds elapsedTimeStack{};

  {
    const auto startTime = std::chrono::high_resolution_clock::now();

    miniStackPushPops(kIter);

    const auto endTime = std::chrono::high_resolution_clock::now();
    elapsedTimeMiniStack = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    std::cout << "miniStack | Elapsed Time: " << elapsedTimeMiniStack << '\n';
  }

  {
    const auto startTime = std::chrono::high_resolution_clock::now();

    stackPushPops(kIter);

    const auto endTime = std::chrono::high_resolution_clock::now();
    elapsedTimeStack = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    std::cout << "std::stack | Elapsed Time: " << elapsedTimeStack << '\n';
  }

  std::cout << "Difference: " << elapsedTimeStack - elapsedTimeMiniStack
            << " | Ratio: " << elapsedTimeStack / elapsedTimeMiniStack << '\n';

  {
    // stackTest();
  }
}

/*
void stackTest()
{
  constexpr int n{ 10 };

  // Constructor test
  MiniStack<int> ministack_A{};
  MiniStack<int> ministack_B{ 2 };

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
  std::cout << "Expected: " << n << " Actual: " << ministack_A.top() << '\n';
  std::cout << "Expected: " << n + 2 << " Actual: " << ministack_B.top() << '\n';

  // Pop test
  std::cout << "Pop\n";
  ministack_A.pop();
  std::cout << "Expected: 1, Actual: " << ministack_A.empty() << '\n';
  std::cout << "Expected: 0, Actual: " << ministack_A.size() << '\n';

  ministack_B.pop();
  std::cout << "Expected: 0, Actual: " << ministack_B.empty() << '\n';
  std::cout << "Expected: 1, Actual: " << ministack_B.size() << '\n';

  ministack_B.pop();
  std::cout << "Expected: 1, Actual: " << ministack_B.empty() << '\n';
  std::cout << "Expected: 0, Actual: " << ministack_B.size() << '\n';

  // Exception test
  int count{};
  try
  {
    while (true)
    {
      ministack_A.push(0);
      ++count;
    }
  }
  catch (const std::runtime_error& e)
  {
    std::cout << count << " : " << e.what() << '\n';
  }

  try
  {
    while (true)
    {
      ministack_A.pop();
      --count;
    }
  }
  catch (const std::runtime_error& e)
  {
    std::cout << count << " : " << e.what() << '\n';
  }

  try
  {
    ministack_A.top();
  }
  catch (const std::runtime_error& e)
  {
    std::cout << count << " : " << e.what() << '\n';
  }
}
*/

void miniStackPushPops(const std::size_t iterations)
{
  MiniStack<int> ministack(iterations);
  for (int i = 0; ministack.size() < iterations; ++i)
  {
    ministack.push(i);
  }
  for (int i = 0; !ministack.empty(); ++i)
  {
    ministack.pop();
  }
}

void stackPushPops(const std::size_t iterations)
{
  std::stack<int> stack;
  for (int i = 0; stack.size() < iterations; ++i)
  {
    stack.push(i);
  }
  for (int i = 0; !stack.empty(); ++i)
  {
    stack.pop();
  }
}