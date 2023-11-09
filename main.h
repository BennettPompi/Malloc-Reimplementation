//
// Created by Clay Shields on 8/25/22.
//

#ifndef MALLOC_MAIN_H
#define MALLOC_MAIN_H

#define FUZZ_RUNS 250000
#define NUM_ALLOCS 250000
#define MAX_ALLOC 2048
#define MIN_ALLOC 20
const int EXP_PARAM = 400;// Selected not at all carefully by just winging it
const double W_MIN = .5;
const double W_MAX = 7;
const char MIN_CHAR = '!';
const char MAX_CHAR = '~';

#endif //MALLOC_MAIN_H
