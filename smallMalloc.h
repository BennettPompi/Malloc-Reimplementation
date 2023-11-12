#pragma once

#define MIN_ALLOC_POWER 5
#define SUPERBLOCKSIZE 4096
#define RETAIN_FREE_SUPERBLOCK_COUNT 4
#define BUCKETS 7
#define MIN_SIZE 32
#define HEADERSIZE 32
#define PAGESIZE 4096
const uint64_t pageMask = 0xfffffffff000;

struct header
{
    //have 32 bytes to work with, this is 31
    header *nextBlock;
    header *lastBlock;
    void *nextAlloc;
    uint16_t allocSize;
    uint16_t bucket;
    uint8_t freeCount;
    uint8_t maxFree;
    char sz;
};
void* smallMalloc(size_t size);
void smallFree(void* ptr);
void smallStats();