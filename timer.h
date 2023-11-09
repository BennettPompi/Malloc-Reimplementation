//
// Created by Clay Shields on 10/27/23.
//

#ifndef MALLOC_SMALL_BASE_TIMER_H
#define MALLOC_SMALL_BASE_TIMER_H
#include "timer.h"
#include <chrono>
#include <iostream>

class timer {
public:
    timer();
    void restart();
    void reset();
    void start();
    void stop();
    long time();
    long total_time();

private:
    std::chrono::time_point<std::chrono::steady_clock> start_time;
    std::chrono::time_point<std::chrono::steady_clock> end_time;
    bool started;
    long total;
};



#endif //MALLOC_SMALL_BASE_TIMER_H
