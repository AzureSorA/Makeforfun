#include<iostream>
#include<typeinfo>
#include<string>
#include<bitset>
#include<memory>
#include<new>

using std::cout;
using std::string;
using std::bitset;


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
                    a = 0;
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
                    b = 1;
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
                    c = 2;
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
#pragma warning(disable: 4250)
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
    namespace template_
    {
        //类模板
        template<typename T>
        class A
        {
        public:
            A(int a,int b)
            {
                this->a = a;
                this->b = b;
            }
            T add()
            {
                return a + b;
            }
        private:
            T a;
            T b;
        };
        //偏特化，范围上的偏特化
        template<typename T>
        class A<T*>
        {
        public:
            T add(T* a, T* b)
            {
                return *a + *b;
            }
        };
        //模板特化，全特化
        template<>
        class A<double>
        {
        public:
            static double mulit(double a, double b)
            {
                return a * b;
            }
        };
        template<typename T1,typename T2>
        class B
        {
        public:
            void output(T1 a,T2 b)
            {
                cout << a << b << "\n";
            }
        };
        //偏特化，参数个数的偏特化
        template<typename T2>
        class B<char, T2>
        {
        public:
            B()
            {
                a = 's';
            }
            void output(T2 b)
            {
                cout << a << b << "\n";
            }
        private:
            char a;
        };
        void instance()
        {
            A<int> a(1, 2); //模板类，将类模板实例化。模板泛化，指使用类模板时指定模板的类型
            cout << a.add() << "\n";
            cout << A<double>::mulit(1.2, 4.3) << "\n";
            A<int*> a1;
            int c1(9), c2(2);
            cout << a1.add(&c1, &c2) << "\n";
        }
    }
}

namespace calculation_
{
    void bit_operation()
    {
        //按位或、与、异或运算符
        int c1 = 9 & 5;
        bitset<8> b1(c1);
        cout << "9 & 5:" << c1 << " "<<b1 << "\n";
        int c2 = 9 | 5;
        b1 = c2;
        cout << "9 | 5:" << c2 << " "<<b1 << "\n";
        int c3 = 9 ^ 5;
        b1 = c3;
        cout << "9 ^ 5:" << c3 << " " << b1 << "\n";

        //取反运算符
        int a = 1;
        cout << "a:" << a << "\n";
        cout << "~a:" << ~a << "\n";
        bitset<32> binary(a);
        cout << "a:" << binary << "\n";
        binary = ~a;
        cout << "~a:" << binary << "\n";
        //正数：原码=反码=补码，复数：反码=原码符号位1不变，其余位取反；补码=反码最低位+1
        //整数在计算机都以二进制补码表示
        //0000 0000 0000 0000 0000 0000 0000 0001(1的补码)
        //取反：1111 1111 1111 1111 1111 1111 1111 1110
        //减一：1111 1111 1111 1111 1111 1111 1111 1101
        //取反得原码：1000 0000 0000 0000 0000 0000 0000 0010

        //左移、右移运算符
        //左移：右边空出的位用0填补，高位左移溢出则舍弃
        //右移：无符号数高位补0，有符号数正数补0，负数取决于系统，补0称为逻辑移位，补1称为算数移位
        bitset<32> b2;
        int d = 5;
        b2 = d;
        cout << "5:" << b2 << "\n";
        b2 = -d;
        cout << "-5:" << b2 << "\n";
        d >>= 2;
        b2 = d;
        cout << "5右移两位之后:" << b2 << "\n";
        d <<= 4;
        b2 = d;
        cout << "5左移四位之后:" << b2 << "\n";
        d = -5;
        d >>= 2;
        b2 = d;
        cout << "-5右移两位之后:" << b2 << "\n";
        d <<= 4;
        b2 = d;
        cout << "-5左移四位之后:" << b2 << "\n";
    }
    void operation_()
    {
        cout << "\n运算符优先级\n";
        cout << "! > 算术运算符 > 关系运算符 > && > || > 赋值运算符\n";
        cout << "\n不可重载运算符\n";
        cout << "成员访问运算符(.)，成员指针访问运算符(.*,->*)，域运算符(::)，长度运算符(sizeof)，条件运算符(?:)，预处理符号(#)\n";
    }
}

namespace value_
{
    //内部最大成员的最宽基本类型成员的整数倍，不足则补齐
    //#pragma pack(n) 以n字节方式对齐
    //结构体为空，其大小为：0 in c,1 in cpp
    struct st
    {
        char a; //1byte
        int b;  //4byte
        char c[5];  //5byte
        int* p; // 32位下，4byte 64位下，8byte
    };
    //
    union u
    {
        short a;    //2byte
        char b;     //1byte
        int c;      //4byte
        long long int d;    //8byte
        float* p;   //32位下，4byte 64位下，8byte
    };
    void value()
    {
        int a = 1;
        short b = 2;
        char c = 'a';
        char s1[] = "hello";
        char s2[6] = "hello";
        char* p1 = s1;
        char* p2 = s2;
        const char* p3 = "hello";
        st s3;
        u u1;
        cout << "size int:" << sizeof(a) << "\n";
        cout << "size short:" << sizeof(b) << "\n";
        cout << "size char:" << sizeof(c) << "\n";
        cout << "s1:" << sizeof(s1) << "\n";
        cout << "s2:" << sizeof(s2) << "\n";
        cout << "p1:" << sizeof(p1) << "\n";
        cout<<strlen(p1)<<"\n";
        cout << "p2:" << sizeof(p2) << "\n";
        cout << "p3:" << sizeof(p3) << "\n";
        cout << strlen(p3) << "\n";
        cout << "s3:" << sizeof(s3) << "\n";
        cout << "u1:" << sizeof(u1) << "\n";
        cout << "memory in s3 struct\n";
        cout << "s3 size:" << sizeof(s3) << "\n";
        cout << " a:" << reinterpret_cast<intptr_t>((&(s3.a))) << "\n";
        cout << " b:" << reinterpret_cast<intptr_t>((&(s3.b))) << "\n";
        cout << " c:" << reinterpret_cast<intptr_t>((&(s3.c))) << "\n";
        cout << " p:" << reinterpret_cast<intptr_t>((&(s3.p))) << "\n";
    }
    /* https:\//www.jianshu.com/p/a5114a581900 */
    int MIT_HAKMEM(unsigned int n)
    {
        unsigned int temp = n;
        temp = n - ((n >> 1) & 033333333333) - ((n >> 2) & 011111111111);
        temp = (temp + (temp >> 3) & 030707070707);
        return (temp % 63);
    }
    int bitcount(unsigned int n)    //not optimization
    {
        unsigned int temp = (n & 010101010101)
            + ((n >> 1) & 010101010101)
            + ((n >> 2) & 010101010101)
            + ((n >> 3) & 010101010101)
            + ((n >> 4) & 010101010101)
            + ((n >> 5) & 010101010101);
        return temp % 63;
    }
}

namespace memory_
{
    //allocate by c
    namespace memory_c
    {
        void allocate_c()
        {
            int* p1 = nullptr;
            p1 = static_cast<int*>(malloc(sizeof(int)*40));
            cout << "p1 address is: " << &p1 << "\n";
            int* p2 = nullptr;
            p2 = static_cast<int*>(calloc(10, sizeof(int)));
            int* p3 = static_cast<int*>(malloc(sizeof(int) * 2));
            cout << "p3 address is: " << &p3 << "\n";
            cout << "p3 size is : " << _msize(p3) << "\n";
            if (p2 != nullptr)
            {
                cout << "p2 address is: " << &p2 << "\n";
                cout << "p2 size is : " << _msize(p2) << "\n";
                int* tmp = static_cast<int*>(realloc(p2, sizeof(int) * 20));
                if (tmp != nullptr)
                {
                    p2 = tmp;
                    cout << "p2 address is: " << &p2 << "\n";
                    cout << "p2 size is : " << _msize(p2) << "\n";
                    cout << "p3 address is: " << &p3 << "\n";
                    cout << "p3 size is : " << _msize(p3) << "\n";
                }
            }
            free(p1);
            free(p2);
            free(p3);
        }
    }
    //allocate by cpp
    namespace memory_cpp
    {
        void allocate_cpp()
        {
            int* p = new int(7);
            cout << *p << "\n";
            int* p1 = new int[10](6);
            cout << p1[0] << "\n";
            int* p2 = new int[5]{ 1,2,3 };
            cout << p2[1] << "\n";
            int(*p3)[3] = new int[3][3]{ 1,2,3,4,5,6 };
            cout << p3[1][1] << "\n";
            int** p4 = new int* [3];
            for (int i = 0; i < 3; ++i)
            {
                p4[i] = new int[3]{ i,i + 1,i + 2 };
            }
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    cout << p4[i][j] << " ";
                }
                cout << "\n";
            }
            for (int i = 0; i < 3; ++i)
            {
                delete[] p4[i];
            }
            delete p;
            delete[] p1;
            delete[] p2;
            delete[] p3;
            delete[] p4;
            //placement new
            //Placement new allows you to construct an object in memory that's already allocated.
            //new (place_address) type
            //new (place_address) type (initializers)
            //new (place_address) type [size]
            //new (place_address) type [size] {braced initializers list}
            class A
            {
            public:
                A()
                {
                    num = 7;
                    cout << "executing constructor.\n";
                }
                ~A()
                {
                    cout << "executing destructor.\n";
                }
                void show()
                {
                    cout << "num: " << num << "\n";
                }
            private:
                int num;
            };
            char* bu = new char[sizeof(string)*4];
            *bu = 's';
            cout << &bu << "\n";
            cout << bu[0] << "\n";
            string* s = new (bu+1)string("hello");
            cout << bu[0] << "\n";
            cout << *s << "\n";
            cout << &s << "\n";
            s->~basic_string(); //不调用析构函数会造成内存泄漏
            delete[] bu;
            
            const int BUF = 512;
            const int N = 5;
            char buffer[BUF];
            double* pd1;
            pd1 = new (buffer) double[N];
            pd1[0] = 1;
            cout << pd1[0] << "\n";
        }
    }
}

int main()
{
    pointer::variable_pointer::pointer();
    pointer::arrary_pointer::pointer();
    pointer::function_pointer::pointer();
    class_::basic::basic_();
    class_::basic::inherit::inherit_();
    class_::template_::instance();
    calculation_::bit_operation();
    calculation_::operation_();
    value_::value();
    cout << "\n" << value_::MIT_HAKMEM(11) << "\n";
    memory_::memory_c::allocate_c();
    memory_::memory_cpp::allocate_cpp();
    onexit(_CrtDumpMemoryLeaks);
    return 0;
}