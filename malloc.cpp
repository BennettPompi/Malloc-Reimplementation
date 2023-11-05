//
// Created by Clay Shields on 8/25/22.
//

#include "malloc.h"
#include <iostream>
#include <sys/mman.h>
#include "timer.h"
using namespace std;

timer mmalloc_timer;
timer mfree_timer;
// struct to make header access easier
struct header
{
    //have 32 bytes to work with, this is 30
    header *nextBlock;
    header *lastBlock;
    void *nextAlloc;
    uint16_t allocSize;
    uint16_t bucket;
    uint8_t freeCount;
    uint8_t maxFree;
    char sz;
};

// array holding pointers to first superblock (page) of each bucket
//{nullptr} initializes all ptrs to nullptr
void *freeBlocks[BUCKETS] = {nullptr};
void *fullBlocks[BUCKETS] = {nullptr};
// arrray of upper size bounds (bytes) for each bucket (we're handling allocations larget that 2048B in next proj)
const uint16_t sizes[BUCKETS] = {MIN_SIZE, 2 * MIN_SIZE, 4 * MIN_SIZE, 8 * MIN_SIZE, 16 * MIN_SIZE, 32 * MIN_SIZE, 64 * MIN_SIZE};
// helper function for initalizing a new block when we need one
const uint64_t pageMask = 0xfffffffff000;
uint16_t extraBlocks = 0;
uint64_t requested = 0;
uint64_t allocated = 0;

void* largeAlloc(size_t size)
{
    
}
void freeBlock(header *block)
{
    if (block->nextBlock)
        block->nextBlock->lastBlock = block->lastBlock;
    if (block->lastBlock)
        block->lastBlock->nextBlock = block->nextBlock;
    else freeBlocks[block->bucket] = block->nextBlock;
    munmap((void*) block, 4096);
}
void swapBlock(header *block)
{
    if (block->nextBlock)
        block->nextBlock->lastBlock = block->lastBlock;
    if (block->lastBlock)
        block->lastBlock->nextBlock = block->nextBlock;
    //if no free, we're swapping to front of full list
    if (block->freeCount == 0)
    {
        //if at head of free block list, fix head pointer, otherwise set it to nullptr
        if (!(block->lastBlock))
            freeBlocks[block->bucket] = block->nextBlock;
        else block->lastBlock = nullptr;
        //swap to head of full
        header* fullHead = (header*)fullBlocks[block->bucket];
        if (fullHead)
            fullHead->lastBlock = block; 
        block->nextBlock = fullHead;
        fullBlocks[block->bucket] = (void*) block; 
    }
    // if free, we're swapping to end of free block list
    else if (block->freeCount == 1)
    {
        //if at head of full, fix head, otherwise set last to nullptr
        if (!(block->lastBlock))
            fullBlocks[block->bucket] = block->nextBlock;
        else block->lastBlock = nullptr;
        //swap to tail of free
        header* freeTail = (header*)freeBlocks[block->bucket];
        while(freeTail && freeTail->nextBlock)
            freeTail = freeTail->nextBlock;
        if (freeTail)
        {
            freeTail->nextBlock = block;
            block->lastBlock = freeTail;
        }
        else 
        {
            freeBlocks[block->bucket] = block;
            block->lastBlock = nullptr;
        }
        block->nextBlock = nullptr; 
    }
}

uint16_t findBucket(size_t size)
{
    for (int i = 0; i < BUCKETS; i++)
    {
        if (size <= sizes[i])
        {
            return i;
        }
    }
    return BUCKETS;
}
void initBlock(void *&blockPtr, uint16_t size)
{
    // initialize header and free list
    header *blockHeader = (header *)blockPtr;
    blockHeader->sz = 'S';
    blockHeader->freeCount = (PAGESIZE / size) - 1;
    blockHeader->maxFree = blockHeader->freeCount;
    blockHeader->allocSize = size;
    blockHeader->bucket = findBucket(size);
    blockHeader->lastBlock = nullptr;

    blockHeader->nextBlock = (header *)freeBlocks[blockHeader->bucket];
    if (blockHeader->nextBlock)
        blockHeader->nextBlock->lastBlock = blockHeader;
    freeBlocks[blockHeader->bucket] = blockPtr;

    blockHeader->nextAlloc = (unsigned char *)blockPtr + size;
    void **freeList = (void **)(blockHeader->nextAlloc);
    for (int i = 1; i < blockHeader->maxFree; i++)
    {
        void *nextAlloc = (void *)((char *)freeList + size);
        *freeList = nextAlloc;
        freeList = (void **)nextAlloc;
    }
    *freeList = nullptr;
}
void *allocate(void *&bucketHead, uint16_t &allocSize, bool newBlock)
{
    header *blockHead = (header *)bucketHead;
    // decrement allocCount by 1
    (blockHead->freeCount)--;
    // link the list back up
    void *retAlloc = blockHead->nextAlloc;
    blockHead->nextAlloc = *((void **)retAlloc);
    if (blockHead->freeCount == 0)
        swapBlock(blockHead);
    if ((blockHead->freeCount == blockHead->maxFree-1) && !newBlock)
        extraBlocks--; 
        
    return retAlloc;
}
void *mmalloc(size_t size)
{
    // determine which bucket to put allocation in
    if (size <= PAGESIZE/2)
    {
        bool createdBlock = false; 
        uint16_t bucket = findBucket(size);
        if (bucket == BUCKETS)
            return nullptr;
        uint16_t allocSize = sizes[bucket];
        requested += size;
        allocated += allocSize;
        // check if free bucket has block in it. If it doesn't, initialize one
        if (!freeBlocks[bucket])
        {
            void *newBlock = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            initBlock(newBlock, allocSize);
            createdBlock = true; 
        }
        // perform allocation
        void *ptr = allocate(freeBlocks[bucket], allocSize, createdBlock);
        return ptr;
    }
    else
    {

    }
}

void mfree(void *ptr)
{
    // perform deallocation
    void *thisBlock = (void *)((uint64_t)ptr & pageMask);
    header *blockHeader = (header *)thisBlock;
    void **alloc = (void **)ptr;
    *alloc = blockHeader->nextAlloc;
    blockHeader->nextAlloc = ptr;
    (blockHeader->freeCount)++;
    if (blockHeader->freeCount == 1)
        swapBlock(blockHeader);
    if (blockHeader->freeCount == blockHeader->maxFree && extraBlocks == RETAIN_FREE_SUPERBLOCK_COUNT)
        freeBlock(blockHeader);
    else if (blockHeader->freeCount == blockHeader->maxFree)
        extraBlocks++; 
    return;
}

void mstats()
{
    double iFrag = ((long double)(allocated - requested)) / allocated;
    uint64_t unusedSpace = 0;
    for (int i = 0; i < BUCKETS; i++)
    {
        uint32_t blocksAlloc = 0;
        uint32_t blocksFree = 0;
        uint32_t allocsUsed = 0;
        uint32_t allocsFree = 0;
        header* blockPtr = (header *)freeBlocks[i];
        while (blockPtr)
        {
            if (blockPtr->freeCount == blockPtr->maxFree)
                blocksFree++;
            else
                blocksAlloc++;

            allocsFree += blockPtr->freeCount;
            allocsUsed += (blockPtr->maxFree - blockPtr->freeCount);
            blockPtr = blockPtr->nextBlock;
        }
        blockPtr = (header*)fullBlocks[i];
        while (blockPtr)
        {
            if (blockPtr->freeCount == blockPtr->maxFree)
                blocksFree++;
            else
                blocksAlloc++;

            allocsFree += blockPtr->freeCount;
            allocsUsed += (blockPtr->maxFree - blockPtr->freeCount);
            blockPtr = blockPtr->nextBlock;
        }
        unusedSpace += (allocsFree * sizes[i]);

        cout << sizes[i] << "B Allocations:" << endl
             << "Superblocks Allocated: " << blocksAlloc << endl
             << "SuperBlocks Free: " << blocksFree << endl
             << "Total Allocated: " << allocsUsed << endl
             << "Allocations Free: " << allocsFree << endl
             << endl;
    }
    cout << "Unused Allocated Space: " << unusedSpace << endl
         << "Internal Fragmentation: " << iFrag << endl;
}
