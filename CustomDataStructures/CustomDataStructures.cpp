/***
 * Data Structures and Testing
 * Jim Diroff II
 *
 * Driver code file | main
 */

#pragma warning(disable : 26446) // ignore unchecked subscript

#include "MiniStack.hpp"
#include "MiniQueue.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <chrono> // high_resolution_clock
#include <stack>
#include <queue>
#include <cstdint>

std::chrono::steady_clock::time_point startTimer();
std::chrono::milliseconds endTimer(const std::chrono::steady_clock::time_point& time);

void queueTest();
void stackTest();

void miniStackPushPops(const std::size_t iterations);
void stackPushPops(const std::size_t iterations);

void miniQueuePushPops(const std::size_t iterations);
void queuePushPops(const std::size_t iterations);

int main()
{
  {
    // stackTest();
    // queueTest();
  }

  {
    /* Set number of iterations for comparisons */
    constexpr std::size_t kIter{ 10000000 };
    /* Set number of iterations for averages */
    constexpr std::size_t kAvgIter{ 10 };

    std::size_t i = 0;

    std::chrono::milliseconds totalMiniStack{};
    std::chrono::milliseconds totalStack{};
    std::chrono::milliseconds totalMiniQueue{};
    std::chrono::milliseconds totalQueue{};

    std::cout << "Running comparisons for " << kIter 
              << " elements\nAveraged over " << kAvgIter << " iterations\n\n";

    while (i++ < kAvgIter) {
      {
        const auto startTime = startTimer();
        miniStackPushPops(kIter);
        std::chrono::milliseconds elapsed = endTimer(startTime);
        totalMiniStack += elapsed;
        //std::cout << "MiniStack: " << elapsed << '\n';
      }

      {
        const auto startTime = startTimer();
        stackPushPops(kIter);
        std::chrono::milliseconds elapsed = endTimer(startTime);
        totalStack += elapsed;
        //std::cout << "Stack: " << elapsed << '\n';
      }

      {
        const auto startTime = startTimer();
        miniQueuePushPops(kIter);
        std::chrono::milliseconds elapsed = endTimer(startTime);
        totalMiniQueue += elapsed;
        //std::cout << "MiniQueue: " << elapsed << '\n';
      }

      {
        const auto startTime = startTimer();
        queuePushPops(kIter);
        std::chrono::milliseconds elapsed = endTimer(startTime);
        totalQueue += elapsed;
        //std::cout << "Queue: " << elapsed << '\n';
      }
    }
    /*
    std::cout << "Average MiniStack Time: "
      << std::chrono::duration_cast<std::chrono::milliseconds>(totalMiniStack).count() / static_cast<double>(kAvgIter) << " milliseconds\n";
    std::cout << "Average Stack Time: "
      << std::chrono::duration_cast<std::chrono::milliseconds>(totalStack).count() / static_cast<double>(kAvgIter) << " milliseconds\n";
    std::cout << "Average MiniQueue Time: "
      << std::chrono::duration_cast<std::chrono::milliseconds>(totalMiniQueue).count() / static_cast<double>(kAvgIter) << " milliseconds\n";
    std::cout << "Average Queue Time: "
      << std::chrono::duration_cast<std::chrono::milliseconds>(totalQueue).count() / static_cast<double>(kAvgIter) << " milliseconds\n";
    */
    double avgMiniStackTime = std::chrono::duration_cast<std::chrono::milliseconds>(totalMiniStack).count() / static_cast<double>(kAvgIter);
    double avgStackTime = std::chrono::duration_cast<std::chrono::milliseconds>(totalStack).count() / static_cast<double>(kAvgIter);
    double avgMiniQueueTime = std::chrono::duration_cast<std::chrono::milliseconds>(totalMiniQueue).count() / static_cast<double>(kAvgIter);
    double avgQueueTime = std::chrono::duration_cast<std::chrono::milliseconds>(totalQueue).count() / static_cast<double>(kAvgIter);

    std::cout << "Average MiniStack Time: " << avgMiniStackTime << " milliseconds\n";
    std::cout << "Average Stack Time: " << avgStackTime << " milliseconds\n";
    std::cout << "Average MiniQueue Time: " << avgMiniQueueTime << " milliseconds\n";
    std::cout << "Average Queue Time: " << avgQueueTime << " milliseconds\n";


    // Comparisons
    double stackTimeDifference = avgStackTime - avgMiniStackTime;
    double stackTimeRatio = avgStackTime / avgMiniStackTime;
    std::cout << "Stack Time Difference (Standard - Custom): " << stackTimeDifference << " milliseconds\n";
    std::cout << "Stack Time Ratio (Standard / Custom): " << stackTimeRatio << "\n";

    double queueTimeDifference = avgQueueTime - avgMiniQueueTime;
    double queueTimeRatio = avgQueueTime / avgMiniQueueTime;
    std::cout << "Queue Time Difference (Standard - Custom): " << queueTimeDifference << " milliseconds\n";
    std::cout << "Queue Time Ratio (Standard / Custom): " << queueTimeRatio << "\n";
  }
}

std::chrono::steady_clock::time_point startTimer() {
  auto time = std::chrono::high_resolution_clock::now();
  return time;
}

std::chrono::milliseconds endTimer(const std::chrono::steady_clock::time_point& time) {
  const auto endTime = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - time);
  /*
  const auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - time);

  std::ostringstream oss{};
  oss << "Elapsed Time: " << elapsedTime << '\n';
  return oss.str();
  */
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

  // Copy and Move Test
  // Create a MiniQueue and populate it
  MiniQueue<int> miniQueue_D;
  for (int i = 0; i < 5; ++i) {
    miniQueue_D.push(i);
  }

  // Test Copy Constructor
  MiniQueue<int> miniQueue_E = miniQueue_D; // Using copy constructor
  std::cout << "After Copy Constructor:\n";
  std::cout << "Queue D front: " << miniQueue_D.front() << ", Queue D back: " << miniQueue_D.back() << '\n';
  std::cout << "Queue E front: " << miniQueue_E.front() << ", Queue E back: " << miniQueue_E.back() << '\n';

  // Test Copy Assignment
  MiniQueue<int> miniQueue_F;
  miniQueue_F = miniQueue_D; // Using copy assignment
  std::cout << "After Copy Assignment:\n";
  std::cout << "Queue D front: " << miniQueue_D.front() << ", Queue D back: " << miniQueue_D.back() << '\n';
  std::cout << "Queue F front: " << miniQueue_F.front() << ", Queue F back: " << miniQueue_F.back() << '\n';

  // Test Move Constructor
  MiniQueue<int> miniQueue_G = std::move(miniQueue_E); // Using move constructor
  std::cout << "After Move Constructor:\n";
  // Note: miniQueue_E is in a valid but unspecified state now
  std::cout << "Queue G front: " << miniQueue_G.front() << ", Queue G back: " << miniQueue_G.back() << '\n';

  // Test Move Assignment
  MiniQueue<int> miniQueue_H;
  miniQueue_H = std::move(miniQueue_F); // Using move assignment
  std::cout << "After Move Assignment:\n";
  // Note: miniQueue_F is in a valid but unspecified state now
  std::cout << "Queue H front: " << miniQueue_H.front() << ", Queue H back: " << miniQueue_H.back() << "\n\n";

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
