#pragma once
#include <sys/mman.h>
#include <stdint.h>
#include "smallMalloc.h"
#define MIN_CAP ((64*1024)/sizeof(size_t))
#define MIN_LOAD .25
#define MAX_LOAD 1
using namespace std;

struct alloc
{
    void* thisAlloc;
    alloc* nextAlloc;
    alloc* lastAlloc;
    uint64_t allocSize;
};

class allocMap
{
    public:
        alloc** table;
        void add(void* addr, uint64_t size, alloc** tbl);
        uint64_t remove(void* addr);

        allocMap();
        ~allocMap();
    private:
        double size;
        uint64_t cap;
        void resizeUp();
        void resizeDown();
        void listDestruct(alloc* a, alloc** newTable);
        uint64_t index(void* addr);   
        void rehash(alloc** tmp, uint64_t &oldCap);
        void moveExisting(alloc* a, alloc** newTable);
        void recMove(alloc* a, alloc** newTable);
};