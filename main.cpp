#include <iostream>
#include <ctime>
#include <cassert>
#include <vector>
#include "teststack.h"
#include "memorypool.h"

#define REPS 1000
#define ELEM 1000



int main()
{
    clock_t start = clock();

    TestStack<int> defaultStack;
    for(int i = 0; i < REPS; i++) {
        //std::cout << "s" << std::endl;
        assert(defaultStack.empty());
        for(int j = 0; j < ELEM; j++)   defaultStack.push(j);
        for(int j = 0; j < ELEM; j++)   defaultStack.pop();
    }
    std::cout << "default allocator uses " << ((double)clock() - start) << std::endl;

    start = clock();
    TestStack<int, MemoryPool<int> > poolStack;
    for(int i = 0; i < REPS; i++) {
        assert(poolStack.empty());
        for(int j = 0; j < ELEM; j++)   poolStack.push(j);
        for(int j = 0; j < ELEM; j++)   poolStack.pop();
    }

    std::cout << "memory pool allocator uses " << ((double)clock() - start) << std::endl;
    return 0;
}

