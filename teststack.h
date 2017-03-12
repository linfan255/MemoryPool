#include <iostream>
#include <ctime>
#include <cassert>
#include <vector>
#include "teststack.h"
#include "memorypool.h"

#define REPS 100000
#define ELEM 50

using namespace std;

int main()
{
	clock_t start = clock();

	TestStack<int> defaultStack;
	for (int i = 0; i < REPS; i++) {
		//std::cout << "s" << std::endl;
		assert(defaultStack.empty());
		for (int j = 0; j < ELEM; j++)   defaultStack.push(j);
		for (int j = 0; j < ELEM; j++)   defaultStack.pop();
	}
	cout << "default allocator of stack uses " << ((double)clock() - start) << endl;

	start = clock();
	vector<int> allocatorVec;
	for (int i = 0; i < REPS; i++) {
		assert(allocatorVec.empty());
		for (int j = 0; j < ELEM; j++)	allocatorVec.push_back(j);
		for (int j = 0; j < ELEM; j++)	allocatorVec.pop_back();
	}
	cout << "default allocator of vector uses " << ((double)clock() - start) << endl;

	start = clock();
	TestStack<int, MemoryPool<int> > poolStack;
	for (int i = 0; i < REPS; i++) {
		assert(poolStack.empty());
		for (int j = 0; j < ELEM; j++)   poolStack.push(j);
		for (int j = 0; j < ELEM; j++)   poolStack.pop();
	}

	cout << "memory pool allocator of stack uses " << ((double)clock() - start) << endl;
	return 0;
}
