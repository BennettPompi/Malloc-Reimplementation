#pragma once
#include <sys/mman.h>
#include <stdint.h>
#include "smallMalloc.h"
#define MIN_CAP ((64*1024)/sizeof(size_t))
#define MIN_LOAD .25
#define MAX_LOAD .75
using namespace std;
/*This is a hash table data structure that uses 
  a chained hash table to store the indices 
  I think the addressing pattern allows us to find a 
  hash function that negates the need for rehashes when
  we increase capacity, but I was unable to find it*/
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
        uint32_t mmapCalls = 0; 
        uint32_t unmapCalls = 0;

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
        void recMove(alloc* a, alloc** newTable);
        void moveExisting(alloc* a, alloc** newTable);

};