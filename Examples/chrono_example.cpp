#include<chrono>
#include<iostream>
#include<iomanip>
#include<thread>

using std::cout;
using std::endl;
using std::setw;
using std::setfill;
bool run = true;

int hour = 23;
int minute = 55;
int second = 55;

void stopwatch()
{
    while (run)
    {
        system("cls");
        cout << setw(2) << setfill('0') << hour << ":";
        cout << setw(2) << setfill('0') << minute << ":";
        cout << setw(2) << setfill('0') << second;
        auto start = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto end= std::chrono::steady_clock::now();
        second += std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        if (second == 60)
        {
            second = 0;
            ++minute;
            if (minute == 60)
            {
                minute = 0;
                ++hour;
                if (hour == 24)
                {
                    hour = 0;
                }
            }
        }
    }
}

void wallclock()
{
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
}


int main()
{
    std::thread t1(stopwatch);
    t1.join();
    
    return 0;
}