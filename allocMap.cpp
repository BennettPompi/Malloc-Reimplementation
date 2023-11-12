#include "allocMap.h"

allocMap::allocMap()
{
    this->cap = PAGESIZE/sizeof(alloc);
    this->size = 0;
    this->table = (alloc*) mmap(nullptr, PAGESIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}
uint32_t allocMap::index(void* addr)
{
    return hash<uint64_t>{}((uint64_t)addr)%this->cap;
}
void allocMap::add(void* addr, uint64_t size, alloc* tbl)
{
    uint32_t index = this->index(addr);
    alloc currAlloc = tbl[index];
    if (currAlloc.thisAlloc)
    {
        while(currAlloc.nextAlloc)
        {
            currAlloc = *currAlloc.nextAlloc;
        }
        alloc* tmp = (alloc*)smallMalloc(sizeof(alloc));
        tmp->allocSize = size;
        tmp->thisAlloc = addr;
        tmp->nextAlloc = nullptr; 
        currAlloc.nextAlloc = tmp;
    }
    else
    {
        currAlloc.allocSize = size;
        currAlloc.thisAlloc = addr;
    }
    this->size++;
    if (this->size/this->cap > .75)
        this->resize();
}
void allocMap::resize()
{
    alloc* tmp = (alloc*)mmap(nullptr, this->cap*2*sizeof(alloc), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    for (int i = 0; i < cap; i++)
    {
        alloc* curr = tmp + i;
        if (curr->thisAlloc)
        {
            this->add(curr->thisAlloc, curr->allocSize, tmp);
            if (curr->nextAlloc)
                this->listDestruct(curr->nextAlloc, tmp);
        }
    }
    munmap(this->table, cap*sizeof(alloc));
    this->table = tmp;
    cap *= 2;
}
void allocMap::listDestruct(alloc* a, alloc* newTable = nullptr)
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
bool allocMap::remove(void* addr)
{
    //written by copilot (wow lol)
    uint32_t index = this->index(addr);
    alloc currAlloc = this->table[index];
    //if there is an alloc in this space, search it for addr
    if (currAlloc.thisAlloc)
    {
        //if the first alloc is the one we want to remove, remove it and free next if applicable
        if (currAlloc.thisAlloc == addr)
        {
            if (currAlloc.nextAlloc)
            {
                alloc* tmp = currAlloc.nextAlloc;
                this->table[index] = *tmp;
                smallFree(tmp);
            }
            else
            {
                currAlloc.thisAlloc = nullptr;
                currAlloc.allocSize = 0;
            }
            this->size--;
            return true;
        }
        //if further in list or non-existent, search list
        else
        {
            while(currAlloc.nextAlloc)
            {
                if (currAlloc.nextAlloc->thisAlloc == addr)
                {
                    alloc* tmp = currAlloc.nextAlloc;
                    currAlloc.nextAlloc = tmp->nextAlloc;
                    smallFree(tmp);
                    this->size--;
                    return true;
                }
                currAlloc = *currAlloc.nextAlloc;
            }
        }
    }
    return false;
}
allocMap::~allocMap()
{
    for (int i = 0; i < cap; i++)
    {
        alloc* a = this->table + i;
        if (a->nextAlloc)
        {
            allocMap::listDestruct(a->nextAlloc);
        }
    }
    munmap(this->table, cap*sizeof(alloc));
}