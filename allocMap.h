#pragma once
#include <sys/mman.h>
#include <functional>
#include <stdint.h>
#include "smallMalloc.h"
using namespace std;

struct alloc
{
    void* thisAlloc;
    alloc* nextAlloc;
    uint32_t allocSize;
};
class allocMap
{
    public:
        alloc* table;
        void add(void* addr, uint64_t size, alloc* tbl);
        bool remove(void* addr);

        allocMap();
        ~allocMap();
    private:
        double size;
        uint32_t cap;
        void resize();
        void listDestruct(alloc* a, alloc* newTable);
        uint32_t index(void* addr);   
};