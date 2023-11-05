//
// Created by Clay Shields on 10/27/23.
//

#include "timer.h"
timer::timer() {
    started = false;
    long total = 0;
}

void timer::reset() {
    total = 0;
}

void timer::start() {
    start_time =  std::chrono::steady_clock::now();
    started = true;
}

void timer::stop() {
    end_time =  std::chrono::steady_clock::now();
    started = false;
    auto diff = std::chrono::duration<long double, std::nano> (end_time - start_time);
    total += (long) diff.count();
}

long timer::total_time(){
    return total;
}

long timer::time() {
    if (started) {
        std::cerr << "timer not stopped" << std::endl;
        return 0;
    }
    auto diff = std::chrono::duration<long double, std::nano> (end_time - start_time);
    return (long) diff.count();
}

