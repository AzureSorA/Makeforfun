#include<iostream>
#include<typeinfo>
#include<string>

using std::cout;
using std::string;


namespace pointer
{
    namespace variable_pointer
    {
        void pointer()
        {
            int a = 0;
            const int b = 1;
            constexpr int c = 2;
            int* p1 = &a;       //指针变量，指向整型变量。
            int const* p3 = &a; //指针变量，指向整型常量。指向的整型不可改变
            int* const p2 = &a; //指针常量，指向整型变量。指针自身不可改变
            const int * const p4 = &a;  //指针常量，指向整型常量。
            
            //char* p = "data"; //non-const pointer, non-const data
            //const char* p = "data"; //non-const pointer, const data
            //char* const p = "data"; //const pointer, non-const data
            //const char* const p = "data"; //const pointer, const data

            cout << typeid(p1).name() << "\n";
            cout << typeid(p2).name() << "\n";
            cout << typeid(p3).name() << "\n";
        }
    }
    namespace arrary_pointer
    {
        void pointer()
        {
            //一二维数组定义方法
            int a[] = { 1,2,3,4,5 };
            int a1[3] = { 1,2,3 };
            //int b[][] = { 1,2,3,4 }; 列不能为空
            int b[][2] = { 1,2,3,4 };
            int b1[2][2] = { 4,3,2,1 };
            int b2[2][2] = { {7,8} ,{5,6} };

            int* p = a;             //指针变量，指向整型一维数组
            int* const p1 = a1;     //指针常量，指向整型一维数组
            int(*p2)[2] = b;        //指针变量，指向整形二维数组
            int(*const p3)[2] = b1; //指针常量，指向整形二维数组

            cout << ** p2 + 1 << "\n";
            cout << **(p2 + 1) << "\n";
        }
    }
    namespace function_pointer
    {
        int* func1(int, int)   //指针函数，返回一个整型指针的函数
        {
            return nullptr;
        }
        //函数指针定义：函数返回值类型 (* 指针变量名) (函数参数列表);
        void func2(int x)
        {
            cout << ++x << "\n";
        }
        double func3(double x, double y)
        {
            return x + y;
        }
        void pointer()
        {
            void(*p)(int) = func2;
            double(*p1)(double, double) = func3;
            int*(*p2)(int, int);
            p2 = func1;
            p(5);
            cout << p1(7.2, 8.4) << "\n";
        }
    }
}

namespace class_
{
    namespace basic
    {
        class A
        {
        public:
            A()
            {
                c = 1;
                b = 2;
                s = "hello";
                std::cout << "执行构造函数\n";
            }
            A(const A& a)//复制构造函数
            {
                c = a.c;
                b = a.b;
                s = a.s;
                ++m;
                std::cout << "执行复制构造函数\n";
            }
            A(A&& a)noexcept//移动构造函数
            {
                c = std::exchange(a.c, 0);
                b = std::exchange(a.b, 0);
                s = std::move(a.s);
                ++m;
                std::cout << "执行移动构造函数\n";
            }
            A& operator=(const A& a)//复制赋值运算符
            {
                c = a.c;
                b = a.b;
                s = a.s;
                std::cout << "执行复制赋值运算符\n";
                return *this;
            }
            A& operator=(A&& a)noexcept//移动赋值运算符
            {
                c = std::exchange(a.c, 0);
                b = std::exchange(a.b, 0);
                s = std::move(a.s);
                std::cout << "执行移动赋值运算符\n";
                return *this;
            }
            ~A()
            {
                std::cout << "执行析构函数\n";
            }
            void output()
            {
                cout << "++m times: " << m << "\n";
            }
            static int m;
        protected:
            int b;
        private:
            int c;
            string s;
        };
        int A::m = 0;
        void basic_()
        {
            A a1;
            A a4(a1);
            A a2 = a1;
            A a3 = std::move(a2);
            a1.output();
        }

        namespace inherit
        {
            //单继承
            class animal
            {
            public:
                virtual void voice() = 0;
            };
            class dog :public animal
            {
            public:
                void voice()
                {
                    cout << "wang wang!!\n";
                }
            };
            class cat :public animal
            {
            public:
                void voice()
                {
                    cout << "nya nya!!\n";
                }
            };

            //多继承
            class A
            {
            public:
                A()
                {
                    cout << "executing A constructor.\n";
                }
                ~A()
                {
                    cout << "executing A destructor.\n";
                }
                void func()
                {
                    cout << "func in A\n";
                }
                virtual void func1()
                {
                    cout << "func1 in A\n";
                }
            private:
                int a;
            };

            class B
            {
            public:
                B()
                {
                    cout << "executing B constructor.\n";
                }
                ~B()
                {
                    cout << "executing B destructor.\n";
                }
                virtual void func2()
                {
                    cout << "func2 in B\n";
                }
                virtual void func3()
                {
                    cout << "func3 in B\n";
                }
            private:
                int b;
            };

            class C :public A, public B
            {
            public:
                C()
                {
                    cout << "executing C destructor.\n";
                }
                ~C()
                {
                    cout << "executing C destructor.\n";
                }
                void func1()
                {
                    cout << "func1 in C\n";
                }
                virtual void func2()
                {
                    cout << "func2 in C\n";
                }
            private:
                int c;
            };

            //虚继承，用来解决菱形继承中派生类拥有多个间接父类实例
            class Base
            {
            public:
                Base()
                {
                    cout << "executing Base constructor.\n";
                }
                ~Base()
                {
                    cout << "executing Base destructor.\n";
                }
                virtual void func()
                {
                    cout << "func in Base\n";
                }
            };

            class Base1 :virtual public Base
            {
            public:
                Base1()
                {
                    cout << "executing Base1 constructor.\n";
                }
                ~Base1()
                {
                    cout << "executing Base1 destructor.\n";
                }
                virtual void func() final   //final标识符说明，其派生类不允许重写该虚函数
                {
                    cout << "func in Base1\n";
                }
                virtual void func1()
                {
                    cout << "func1 in Base1\n";
                }
            };

            class Base2 :virtual public Base
            {
            public:
                Base2()
                {
                    cout << "executing Base1 constructor.\n";
                }
                ~Base2()
                {
                    cout << "executing Base1 destructor.\n";
                }
                virtual void func2()
                {
                    cout << "func2 in Base2\n";
                }
            };

            class Derive :public Base1, public Base2
            {
            public:
                Derive()
                {
                    cout << "executing Derive constructor.\n";
                }
                ~Derive()
                {
                    cout << "executing Derive destructor.\n";
                }
                virtual void func1()
                {
                    cout << "func1 in Derive\n";
                }
                virtual void func2()
                {
                    cout << "func2 in Derive\n";
                }
            };

            void inherit_()
            {
                dog dog_;
                cat cat_;
                dog_.voice();
                cat_.voice();
                C c;
                A* p = &c;
                p->func();
                p->func1();
                c.func2();
                c.func3();
                p = nullptr;

                Derive* d = new Derive();
                d->func();
                d->func1();
                d->func2();
                delete d;
            }
        }
    }
}

namespace calculation
{

}

int main()
{
    pointer::variable_pointer::pointer();
    pointer::arrary_pointer::pointer();
    pointer::function_pointer::pointer();
    class_::basic::basic_();
    class_::basic::inherit::inherit_();

    return 0;
}