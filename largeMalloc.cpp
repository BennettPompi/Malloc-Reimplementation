#include "largeMalloc.h"
double largePages = 0;
uint64_t largeBytes = 0; 
uint64_t currPages = 0; 
uint64_t currBytes = 0; 


allocMap allocs;
void* largeMalloc(size_t size)
{
    largeBytes += size;
    currBytes += size; 
    uint64_t allocPages = size/PAGESIZE;
    if (size%PAGESIZE > 0)
        allocPages++;
    largePages += allocPages;
    currPages += allocPages;
    void* allocation = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    allocs.add(allocation, size, allocs.table);
    return allocation;
}
bool largeFree(void* alloc)
{
    uint64_t allocSize = allocs.remove(alloc);
    if (allocSize != 0)
    {
        uint64_t allocPages = allocSize/PAGESIZE;
        if (allocSize%PAGESIZE > 0)
            allocPages++;
        currPages -= allocPages;
        currBytes -= allocSize; 
        munmap(alloc, allocSize);
        return true;
    }
    else
        return false;
}
void largeStats()
{
    cout << "Large Allocations: " << endl;
    cout << " - Cumulative Pages Allocated: " << largePages << endl
    << " - Cumulative Bytes Allocated: " << largeBytes << endl
    << " - Cumulative Internal Fragmentation: " 
    << (1-(largeBytes/(largePages * PAGESIZE)))*100 << endl
    << " - Current Pages Allocated: " << currPages << endl
    << "Index mmap calls: " << allocs.mmapCalls << endl
    << "Index munmap calls: " << allocs.unmapCalls << endl
    << "Index current allocated bytes:" << currBytes << endl << endl; 

}