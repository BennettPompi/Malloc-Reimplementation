#include "allocMap.h"
#include <sys/mman.h>
#include <iostream>
void* largeMalloc(size_t size);
bool largeFree(void* alloc);
void largeStats();