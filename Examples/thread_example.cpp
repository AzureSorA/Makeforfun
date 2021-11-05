#include<iostream>
#include<thread>
#include<future>
#include<mutex>

bool run = true;
std::mutex run_mutex;

void f1(int n)
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "thread executing f1()\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}

void f2(int& n)
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "thread executing f2()\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}

void f3()
{
    std::lock_guard<std::mutex> lock(run_mutex);    //尝试获得mutex所有权
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "thread executing f3()\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    run = false;
}

class A
{
public:
    void fa()
    {
        for (int i = 0; i < 5; ++i)
        {
            std::cout << "thread executing fa()\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::microseconds(10));
        }
    }
    int n = 0;
};

class B
{
public:
    void operator()()
    {
        for (int i = 0; i < 5; ++i)
        {
            std::cout << "thread executing B()\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::microseconds(10));
        }
    }
    int n = 0;
};

void thread_example1()
{
    int n = 0;
    A a;
    B b;
    std::cout << std::thread::hardware_concurrency() << " concurrent threads are supported.\n";
    std::thread t1; //构造不表示线程的新thread对象
    std::cout << "t1 id is: " << t1.get_id() << std::endl;
    std::cout << "t1 joinable: " << t1.joinable() << std::endl;
    std::cout << "t1 handle is : " << t1.native_handle() << std::endl;
    std::thread t2(f1, n + 1);  //按值传递
    std::cout << "t2 id is: "<<t2.get_id() << std::endl;
    std::cout << "t2 joinable: " << t2.joinable() << std::endl;
    std::cout << "t2 handle is : " << t2.native_handle() << std::endl;
    std::thread t3(f2, std::ref(n));    //按引用传递
    std::thread t4(std::move(t3));      //移动构造，t3不再是线程
    std::thread t5(&A::fa, &a);         //在对象a上运行A::fa
    std::thread t6(b);                  //在对象b的副本运行b::operator()
    t2.join();
    std::cout << "after join,t2 joinable: " << t2.joinable() << std::endl;
    t4.join();
    t5.join();
    t6.join();
    std::cout << "n is " << n << "\n";
    std::cout << "n in A is " << a.n << "\n";
    std::cout << "n in B is " << b.n << "\n";
    std::cout << "********************************************************************\n\n";
    std::thread t7(f1,5);
    std::thread t8(f2,std::ref(n));
    std::cout << "t7 id is: " << t7.get_id() << std::endl;
    std::cout << "t8 id is: " << t8.get_id() << std::endl;
    std::swap(t7, t8);
    std::cout << "t7 id is: " << t7.get_id() << std::endl;
    std::cout << "t8 id is: " << t8.get_id() << std::endl;
    t7.swap(t8);
    std::cout << "t7 id is: " << t7.get_id() << std::endl;
    std::cout << "t8 id is: " << t8.get_id() << std::endl;
    t7.join();
    t8.join();
    std::thread t9(f3);
    t9.detach();
    while (run){}
}

int main()
{
    thread_example1();
    return 0;
}
