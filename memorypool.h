#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <climits>
#include <cstddef>

template<typename T, size_t BlockSize = 4096>
class MemoryPool
{
public:
    MemoryPool() {
        curr_block = nullptr;
        curr_slot = nullptr;
        free_slot = nullptr;
        last_slot = nullptr;
    }

    ~MemoryPool() {
        memory_slot* curr = curr_block;
        while(curr != nullptr) {
            memory_slot* next_p = curr->next;
            operator delete(reinterpret_cast<void*>(curr));
            curr = next_p;
        }
    }

    T* allocate(size_t n = 1) {
        if(free_slot != nullptr) {
            T* ret = reinterpret_cast<T*>(free_slot);
            free_slot = free_slot->next;
            return ret;
        } else {
            if(curr_slot == last_slot) {
                char* new_block = reinterpret_cast<char*>(operator new(BlockSize));
                reinterpret_cast<memory_slot*>(new_block)->next = curr_block;
                curr_block = reinterpret_cast<memory_slot*>(new_block);

                char* body = new_block + sizeof(memory_slot*);
                uintptr_t pos = reinterpret_cast<uintptr_t>(body);
                size_t padding = (alignof(memory_slot) - pos) % alignof(memory_slot);

                curr_slot = reinterpret_cast<memory_slot*>(body + padding);
                last_slot = reinterpret_cast<memory_slot*>(new_block + BlockSize - sizeof(memory_slot));
            }
            return reinterpret_cast<T*>(curr_slot++);
        }
    }

    template<typename U>
    void destroy(U* p) {
        p->~U();
    }

    void deallocate(T* p, size_t n = 1) {
        if(p != nullptr) {
            reinterpret_cast<memory_slot*>(p)->next = free_slot;
            free_slot = reinterpret_cast<memory_slot*>(p);
        }
    }

    template<typename U, typename... Arg>
    void construct(U* p, Arg&&... arg) {
        new(p) U (std::forward<Arg>(arg)...);
    }

    template<typename U>
    struct rebind {
      typedef MemoryPool<U> other;
    };

private:
    union memory_slot {
        T val;
        memory_slot* next;
    };
    memory_slot* curr_block;
    memory_slot* curr_slot;
    memory_slot* free_slot;
    memory_slot* last_slot;
};



#endif // MEMORYPOOL_H
