#include "allocMap.h"

uint64_t hash(uint64_t x) 
{
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x;
}
allocMap::allocMap()
{
    this->cap = ((16*PAGESIZE)/sizeof(alloc*));
    this->size = 0;
    this->table = (alloc**) mmap(nullptr, PAGESIZE*16, PROT_READ | 
                            PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}
uint64_t allocMap::index(void* addr)
{
    uint64_t index = hash((uint64_t) addr);
    index = index % this->cap; 
    return index;
}
void allocMap::add(void* addr, uint64_t size, alloc** tbl)
{
    uint32_t index = this->index(addr);
    alloc** head = tbl + index;
    alloc* currAlloc = *head; 
    if (currAlloc)
    {
        while(currAlloc->nextAlloc)
        {
            currAlloc = currAlloc->nextAlloc;
        }
        alloc* tmp = (alloc*)smallMalloc(sizeof(alloc));
        tmp->allocSize = size;
        tmp->thisAlloc = addr;
        tmp->nextAlloc = nullptr; 
        tmp->lastAlloc = currAlloc;
        currAlloc->nextAlloc = tmp;
    }
    else
    {
        currAlloc = (alloc*)smallMalloc(sizeof(alloc));
        currAlloc->allocSize = size;
        currAlloc->thisAlloc = addr;
        currAlloc->nextAlloc = nullptr; 
        currAlloc->lastAlloc = nullptr;
        *head = currAlloc; 
    }
    this->size++;
    if (this->size/this->cap > MAX_LOAD)
        this->resizeUp();
}
void allocMap::recMove(alloc* a, alloc** newTable)
{
    if (!a->nextAlloc)
    {
        this->moveExisting(a, newTable);
        return;
    }
    this->recMove(a->nextAlloc, newTable);
    this->moveExisting(a, newTable);
    return;
}
void allocMap::moveExisting(alloc* a, alloc** newTable)
{
    uint64_t index = this->index(a->thisAlloc);
    alloc** head = newTable + index;
    a->lastAlloc = nullptr;
    a->nextAlloc = nullptr; 
    alloc* curr = *head;
    if (! curr)
    {
        *head = a; 
    }
    else
    {
        while(curr->nextAlloc)
            curr = curr->nextAlloc;
        curr->nextAlloc = a;
        a->lastAlloc = curr; 
    }
}
void allocMap::rehash(alloc** tmp, uint64_t &oldCap)
{
    alloc** curr = this->table;
    for (int i = 0; i < oldCap; i++)
    {
        if (*curr)
        {
            recMove(*curr, tmp);
        }
        curr++; 
    }
}
void allocMap::resizeUp()
{
    uint64_t oldCap = this->cap;
    this->cap *= 2; 
    this->mmapCalls ++; 
    alloc** tmp = (alloc**)mmap(nullptr, this->cap*(sizeof(alloc)), 
                        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    this->rehash(tmp, oldCap);
    this->unmapCalls++;
    munmap((void*)(this->table), (oldCap*sizeof(alloc*)));
    this->table = tmp;
}
void allocMap::resizeDown()
{
    uint64_t oldCap = this->cap;
    this->cap /= 2; 
    this->mmapCalls++;
    alloc** tmp = (alloc**)mmap(nullptr, this->cap*(sizeof(alloc)), 
                        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    this->rehash(tmp, oldCap);
    this->unmapCalls++;
    munmap(this->table, cap*sizeof(alloc));
    this->table = tmp;
}
void allocMap::listDestruct(alloc* a, alloc** newTable = nullptr)
{
    if(newTable)
        this->add(a->thisAlloc,a->allocSize, newTable);
    if (!a->nextAlloc)
    {
        smallFree(a);
        return;
    }
    listDestruct(a->nextAlloc);
    smallFree(a);
    return; 
}
uint64_t allocMap::remove(void* addr)
{
    //written by copilot (wow lol)
    uint32_t index = this->index(addr);
    alloc** head = this->table + index;
    alloc* curr = *head;
    uint32_t ret = 0; 
    //if there is an alloc in this space, search it for addr
    if (curr)
    {
        //if the first alloc is the one we want to remove, remove it and free next if applicable
        if (curr->thisAlloc == addr)
        {
            ret = curr->allocSize;
            if (curr->nextAlloc)
            {
                alloc* tmp = curr->nextAlloc;
                tmp->lastAlloc = nullptr;
                *head = tmp;
            }
            else
            {
                *head = nullptr;
            }
            smallFree(curr);
            this->size--;
        }
        //if further in list or non-existent, search list
        else
        {
            while(curr)
            {
                if (curr->thisAlloc == addr)
                {
                    ret = curr->allocSize;
                    curr->lastAlloc->nextAlloc = curr->nextAlloc;
                    if (curr->nextAlloc)
                        curr->nextAlloc->lastAlloc = curr->lastAlloc;
                    this->size--; 
                    break;
                }
                curr = curr->nextAlloc;
            }
        }
    }
    if (ret > 0 && this->cap > MIN_CAP && (this->size/this->cap) < MIN_LOAD)
        resizeDown();
    return ret;
}
allocMap::~allocMap()
{
    alloc** a;
    for (int i = 0; i < cap; i++)
    {
        a = this->table + i;
        if (*a)
        {
            allocMap::listDestruct(*a);
        }
    }
    munmap(this->table, cap*sizeof(alloc));
}