//
// Created by Clay Shields on 8/25/22.
//

#ifndef MALLOC_MALLOC_H
#define MALLOC_MALLOC_H
#include <stdio.h>
#include "timer.h"

#define MIN_ALLOC_POWER 5
#define PAGESIZE 4096
#define SUPERBLOCKSIZE 4096
#define RETAIN_FREE_SUPERBLOCK_COUNT 4
#define BUCKETS 7
#define MIN_SIZE 32
#define HEADERSIZE 32
void * mmalloc (size_t __size);
void mfree(void*);
void mstats();

// timers for performance measurements
extern timer mmalloc_timer;
extern timer mfree_timer;

#endif //MALLOC_MALLOC_H
