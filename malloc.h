//
// Created by Clay Shields on 8/25/22.
//

#pragma once
#include <stdio.h>
#include "timer.h"
#include "smallMalloc.h"
#define PAGESIZE 4096
void * mmalloc (size_t __size);
void mfree(void*);
void mstats();

// timers for performance measurements
extern timer mmalloc_timer;
extern timer mfree_timer;
