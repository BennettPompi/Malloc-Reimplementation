#include "allocMap.h"
#include <sys/mman.h>

void* largeMalloc(size_t size);
bool largeFree(void* &alloc);
void largeStats();