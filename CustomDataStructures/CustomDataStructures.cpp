/***
 * Data Structures and Testing
 * Jim Diroff II
 *
 * Driver code file | main
 */

#include "MiniStack.hpp"
#include "MiniQueue.hpp"
#include <iostream>
#include <chrono> // high_resolution_clock
#include <stack>
#include <queue>
#include <cstdint>

void stackTest();
void queueTest();

void miniStackPushPops(const std::size_t iterations);
void stackPushPops(const std::size_t iterations);

void miniQueuePushPops(const std::size_t iterations);
void queuePushPops(const std::size_t iterations);

int main()
{
  {
    // stackTest();
    //queueTest();
  }
  
  constexpr std::size_t kIter{ 1000 };

  {
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
      << " | Ratio: " << elapsedTimeStack / elapsedTimeMiniStack << "\n\n";
  }

  {
    std::chrono::nanoseconds elapsedTimeMiniQueue{};
    std::chrono::nanoseconds elapsedTimeQueue{};

    {
      const auto startTime = std::chrono::high_resolution_clock::now();

      miniQueuePushPops(kIter);

      const auto endTime = std::chrono::high_resolution_clock::now();
      elapsedTimeMiniQueue = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
      std::cout << "miniQueue | Elapsed Time: " << elapsedTimeMiniQueue << '\n';
    }

    {
      const auto startTime = std::chrono::high_resolution_clock::now();

      queuePushPops(kIter);

      const auto endTime = std::chrono::high_resolution_clock::now();
      elapsedTimeQueue = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
      std::cout << "std::queue | Elapsed Time: " << elapsedTimeQueue << '\n';
    }

    std::cout << "Difference: " << elapsedTimeQueue - elapsedTimeMiniQueue
      << " | Ratio: " << elapsedTimeQueue / elapsedTimeMiniQueue << "\n\n";
  }

  
}

void queueTest() {
  constexpr int n{ 10 };

  // Constructor Test
  MiniQueue<int> miniQueue_A{};
  MiniQueue<int> miniQueue_B{ 2 };

  // Empty Test
  std::cout << "Empty\n";
  std::cout << "Expected: 1, Actual: " << miniQueue_A.empty() << '\n';
  std::cout << "Expected: 1, Actual: " << miniQueue_B.empty() << '\n';
  std::cout << "Expected: 0, Actual: " << miniQueue_A.size() << '\n';
  std::cout << "Expected: 0, Actual: " << miniQueue_B.size() << '\n';

  // Push test
  std::cout << "Push\n";
  miniQueue_A.push(n);
  std::cout << "Expected: 0, Actual: " << miniQueue_A.empty() << '\n';
  std::cout << "Expected: 1, Actual: " << miniQueue_A.size() << '\n';

  miniQueue_B.push(n + 1);
  std::cout << "Expected: 0, Actual: " << miniQueue_B.empty() << '\n';
  std::cout << "Expected: 1, Actual: " << miniQueue_B.size() << '\n';
  miniQueue_B.push(n + 2);
  std::cout << "Expected: 0, Actual: " << miniQueue_B.empty() << '\n';
  std::cout << "Expected: 2, Actual: " << miniQueue_B.size() << '\n';

  // Access test
  std::cout << "Front\n";
  std::cout << "Expected: 10, Actual: " << miniQueue_A.front() << '\n';
  std::cout << "Expected: 10, Actual: " << miniQueue_A.back() << '\n';
  std::cout << "Expected: 11, Actual: " << miniQueue_B.front() << '\n';
  std::cout << "Expected: 12, Actual: " << miniQueue_B.back() << '\n';

  // Pop test
  std::cout << "Pop\n";
  miniQueue_A.pop();
  std::cout << "Expected: 1, Actual: " << miniQueue_A.empty() << '\n';
  std::cout << "Expected: 0, Actual: " << miniQueue_A.size() << '\n';

  miniQueue_B.pop();
  std::cout << "Expected: 0, Actual: " << miniQueue_B.empty() << '\n';
  std::cout << "Expected: 1, Actual: " << miniQueue_B.size() << '\n';

  miniQueue_B.pop();
  std::cout << "Expected: 1, Actual: " << miniQueue_B.empty() << '\n';
  std::cout << "Expected: 0, Actual: " << miniQueue_B.size() << '\n';

  // Windowing queue test
  std::cout << "Windowing Queue\n";
  for (int i{ 0 }; i < 10; ++i) {
    miniQueue_A.push(i);
  }
  miniQueue_A.pop(); // pop 0
  miniQueue_A.pop(); // pop 1
  miniQueue_A.pop(); // pop 2
  miniQueue_A.push(47); // queue 47
  miniQueue_A.push(48); // queue 48

  std::cout << miniQueue_A.front() << ' ' << miniQueue_A.back() << '\n';

  for (int i{ 0 }; i < 7; ++i) {
    miniQueue_A.pop();
  }

  std::cout << miniQueue_A.front() << ' ' << miniQueue_A.back() << '\n';

  miniQueue_A.pop();
  miniQueue_A.push(127);
  std::cout << miniQueue_A.front() << ' ' << miniQueue_A.back() << '\n';
  
  // Exception test
  int count{};
  MiniQueue<int> miniQueue_C{};
  try
  {
    while (true)
    {
      miniQueue_C.push(0);
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
      miniQueue_C.pop();
      --count;
    }
  }
  catch (const std::runtime_error& e)
  {
    std::cout << count << " : " << e.what() << '\n';
  }

  try
  {
    miniQueue_C.front();
  }
  catch (const std::runtime_error& e)
  {
    std::cout << count << " : " << e.what() << '\n';
  }

  try
  {
    miniQueue_C.back();
  }
  catch (const std::runtime_error& e)
  {
    std::cout << count << " : " << e.what() << '\n';
  }
}

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

void miniQueuePushPops(const std::size_t iterations)
{
  MiniQueue<int> miniQueue(iterations);
  for (int i = 0; miniQueue.size() < iterations; ++i)
  {
    miniQueue.push(i);
  }

  for (int i = 0; !miniQueue.empty(); ++i)
  {
    miniQueue.pop();
  }
}

void queuePushPops(const std::size_t iterations)
{
  std::queue<int> queue;
  for (int i = 0; queue.size() < iterations; ++i)
  {
    queue.push(i);
  }

  for (int i = 0; !queue.empty(); ++i)
  {
    queue.pop();
  }
}
