#pragma once
#include<chrono>
#include<thread>

class Timer
{
public:
    Timer();
    ~Timer() = default;
    void start();
    void stop();
    void reset();
    int get_time();
    bool is_running();
private:
    int time_;
    bool run_;

    void second_counter();
};

