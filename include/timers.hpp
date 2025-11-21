#pragma once
#include <chrono>
#include <cassert>

template <typename DT = std::chrono::microseconds, typename ClockT = std::chrono::steady_clock>

class Timer
{
    using timep_t = typename ClockT::time_point;
    timep_t _start = ClockT::now(), _end = {};

public:
    void tick() { 
        _end = timep_t{}; 
        _start = ClockT::now(); 
    }
    
    void tock() { _end = ClockT::now(); }
    
    template <typename T = DT> 
    auto duration() const { 
        assert(_end != timep_t{} && "toc before reporting");
        return std::chrono::duration_cast<T>(_end - _start); 
    }
};