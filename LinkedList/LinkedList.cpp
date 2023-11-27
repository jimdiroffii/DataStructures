
#include "MiniList.hpp"
#include <iostream> // cout
#include <ios> // boolalpha

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif


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
    std::cout << "front: " << miniList.front() << '\n';
    std::cout << "back: " << miniList.back() << '\n';

    int a = 1;
    miniList.push_front(a);

    std::cout << "\npush_front: 1\n";
    std::cout << "front: " << miniList.front() << '\n';
    std::cout << "back: " << miniList.back() << '\n';

    int b = 2;
    miniList.push_front(b);

    std::cout << "push_front: 2\n";
    std::cout << "front: " << miniList.front() << '\n';
    std::cout << "back: " << miniList.back() << '\n';

    int c = 3;
    miniList.push_back(c);

    std::cout << "push_back: 3\n";
    std::cout << "front: " << miniList.front() << '\n';
    std::cout << "back: " << miniList.back() << '\n';

    int d = 4;
    miniList.push_back(d);

    std::cout << "push_back: 4\n";
    std::cout << "front: " << miniList.front() << '\n';
    std::cout << "back: " << miniList.back() << '\n';

    miniList.pop_back();
    
    std::cout << "\npop_back:\n";
    std::cout << "front: " << miniList.front() << '\n';
    std::cout << "back: " << miniList.back() << '\n';

    miniList.pop_front();

    std::cout << "pop_front:\n";
    std::cout << "front: " << miniList.front() << '\n';
    std::cout << "back: " << miniList.back() << '\n';

    miniList.pop_back();

    std::cout << "pop_back:\n";
    std::cout << "front: " << miniList.front() << '\n';
    std::cout << "back: " << miniList.back() << '\n';

    miniList.pop_front();

    std::cout << "pop_front:\n";
    std::cout << "front: " << miniList.front() << '\n';
    std::cout << "back: " << miniList.back() << '\n';

  }

#ifdef _DEBUG
  // Report any memory leaks
  _CrtDumpMemoryLeaks();
#endif

}
