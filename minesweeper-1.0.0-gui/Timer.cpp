#include "Timer.h"

Timer::Timer()
{
    time_ = 0;
    run_ = false;
}

void Timer::start()
{
    run_ = true;
    std::thread t1(&Timer::second_counter, this);
    t1.detach();
}

void Timer::stop()
{
    run_ = false;
}

void Timer::second_counter()
{
    while (run_)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto end = std::chrono::high_resolution_clock::now();
        time_ += std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    }
}

void Timer::reset()
{
    time_ = 0;
}

int Timer::get_time()
{
    return time_;
}

bool Timer::is_running()
{
    return run_;
}