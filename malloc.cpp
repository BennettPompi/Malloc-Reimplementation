//
// Created by Clay Shields on 8/25/22.
//

#include "malloc.h"
#include "smallMalloc.h"
#include "largeMalloc.h"
#include <iostream>
#include <sys/mman.h>
#include "timer.h"
using namespace std;

timer mmalloc_timer;
timer mfree_timer;
// struct to make header access easier

// array holding pointers to first superblock (page) of each bucket
//{nullptr} initializes all ptrs to nullptr

uint64_t largeAllocated;
uint64_t largeRequested; 

void *mmalloc(size_t size)
{
    void* ptr; 
    mmalloc_timer.start();
    // determine which bucket to put allocation in
    if (size <= PAGESIZE/2)
    {
       ptr = smallMalloc(size);
    }
    else
    {
        ptr = largeMalloc(size);
    }
    mmalloc_timer.stop();
    return ptr; 
}

void mfree(void *ptr)
{
    mfree_timer.start();
    // perform deallocation

    if (!largeFree(ptr)) //not in allocTable
    {
        smallFree(ptr);
    }
    mfree_timer.stop();
    return;
}

void mstats()
{
    largeStats();
    smallStats();
    cout << "Total mmalloc time: " << mmalloc_timer.total_time() << endl;
    cout << "Total mfree time: " << mfree_timer.total_time() << endl;
    cout << "Total time spent in malloc: " << mfree_timer.total_time() + mmalloc_timer.total_time() << endl;
}
