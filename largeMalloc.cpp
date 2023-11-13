#include "largeMalloc.h"
allocMap allocs;
void* largeMalloc(size_t size)
{
    void* allocation = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    allocs.add(allocation, size, allocs.table);
    return allocation;
}
bool largeFree(void* alloc)
{
    uint64_t allocSize = allocs.remove(alloc);
    if (allocSize != 0)
    {
        munmap(alloc, allocSize);
        return true;
    }
    else
        return false;
}
void largeStats()
{

}