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
            int* p1 = &a;       //ָ�������ָ�����ͱ�����
            int const* p3 = &a; //ָ�������ָ�����ͳ�����ָ������Ͳ��ɸı�
            int* const p2 = &a; //ָ�볣����ָ�����ͱ�����ָ�������ɸı�
            const int * const p4 = &a;  //ָ�볣����ָ�����ͳ�����
            
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
            //һ��ά���鶨�巽��
            int a[] = { 1,2,3,4,5 };
            int a1[3] = { 1,2,3 };
            //int b[][] = { 1,2,3,4 }; �в���Ϊ��
            int b[][2] = { 1,2,3,4 };
            int b1[2][2] = { 4,3,2,1 };
            int b2[2][2] = { {7,8} ,{5,6} };

            int* p = a;             //ָ�������ָ������һά����
            int* const p1 = a1;     //ָ�볣����ָ������һά����
            int(*p2)[2] = b;        //ָ�������ָ�����ζ�ά����
            int(*const p3)[2] = b1; //ָ�볣����ָ�����ζ�ά����

            cout << ** p2 + 1 << "\n";
            cout << **(p2 + 1) << "\n";
        }
    }
    namespace function_pointer
    {
        int* func1(int, int)   //ָ�뺯��������һ������ָ��ĺ���
        {
            return nullptr;
        }
        //����ָ�붨�壺��������ֵ���� (* ָ�������) (���������б�);
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
                std::cout << "ִ�й��캯��\n";
            }
            A(const A& a)//���ƹ��캯��
            {
                c = a.c;
                b = a.b;
                s = a.s;
                ++m;
                std::cout << "ִ�и��ƹ��캯��\n";
            }
            A(A&& a)noexcept//�ƶ����캯��
            {
                c = std::exchange(a.c, 0);
                b = std::exchange(a.b, 0);
                s = std::move(a.s);
                ++m;
                std::cout << "ִ���ƶ����캯��\n";
            }
            A& operator=(const A& a)//���Ƹ�ֵ�����
            {
                c = a.c;
                b = a.b;
                s = a.s;
                std::cout << "ִ�и��Ƹ�ֵ�����\n";
                return *this;
            }
            A& operator=(A&& a)noexcept//�ƶ���ֵ�����
            {
                c = std::exchange(a.c, 0);
                b = std::exchange(a.b, 0);
                s = std::move(a.s);
                std::cout << "ִ���ƶ���ֵ�����\n";
                return *this;
            }
            ~A()
            {
                std::cout << "ִ����������\n";
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
            //���̳�
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

            //��̳�
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

            //��̳У�����������μ̳���������ӵ�ж����Ӹ���ʵ��
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
                virtual void func() final   //final��ʶ��˵�����������಻������д���麯��
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
        //��ģ��
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
        //ƫ�ػ�����Χ�ϵ�ƫ�ػ�
        template<typename T>
        class A<T*>
        {
        public:
            T add(T* a, T* b)
            {
                return *a + *b;
            }
        };
        //ģ���ػ���ȫ�ػ�
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
        //ƫ�ػ�������������ƫ�ػ�
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
            A<int> a(1, 2); //ģ���࣬����ģ��ʵ������ģ�巺����ָʹ����ģ��ʱָ��ģ�������
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
        //��λ���롢��������
        int c1 = 9 & 5;
        bitset<8> b1(c1);
        cout << "9 & 5:" << c1 << " "<<b1 << "\n";
        int c2 = 9 | 5;
        b1 = c2;
        cout << "9 | 5:" << c2 << " "<<b1 << "\n";
        int c3 = 9 ^ 5;
        b1 = c3;
        cout << "9 ^ 5:" << c3 << " " << b1 << "\n";

        //ȡ�������
        int a = 1;
        cout << "a:" << a << "\n";
        cout << "~a:" << ~a << "\n";
        bitset<32> binary(a);
        cout << "a:" << binary << "\n";
        binary = ~a;
        cout << "~a:" << binary << "\n";
        //������ԭ��=����=���룬����������=ԭ�����λ1���䣬����λȡ��������=�������λ+1
        //�����ڼ�������Զ����Ʋ����ʾ
        //0000 0000 0000 0000 0000 0000 0000 0001(1�Ĳ���)
        //ȡ����1111 1111 1111 1111 1111 1111 1111 1110
        //��һ��1111 1111 1111 1111 1111 1111 1111 1101
        //ȡ����ԭ�룺1000 0000 0000 0000 0000 0000 0000 0010

        //���ơ����������
        //���ƣ��ұ߿ճ���λ��0�����λ�������������
        //���ƣ��޷�������λ��0���з�����������0������ȡ����ϵͳ����0��Ϊ�߼���λ����1��Ϊ������λ
        bitset<32> b2;
        int d = 5;
        b2 = d;
        cout << "5:" << b2 << "\n";
        b2 = -d;
        cout << "-5:" << b2 << "\n";
        d >>= 2;
        b2 = d;
        cout << "5������λ֮��:" << b2 << "\n";
        d <<= 4;
        b2 = d;
        cout << "5������λ֮��:" << b2 << "\n";
        d = -5;
        d >>= 2;
        b2 = d;
        cout << "-5������λ֮��:" << b2 << "\n";
        d <<= 4;
        b2 = d;
        cout << "-5������λ֮��:" << b2 << "\n";
    }
    void operation_()
    {
        cout << "\n��������ȼ�\n";
        cout << "! > ��������� > ��ϵ����� > && > || > ��ֵ�����\n";
        cout << "\n�������������\n";
        cout << "��Ա���������(.)����Աָ����������(.*,->*)���������(::)�����������(sizeof)�����������(?:)��Ԥ�������(#)\n";
    }
}

namespace value_
{
    //�ڲ�����Ա�����������ͳ�Ա������������������
    //#pragma pack(n) ��n�ֽڷ�ʽ����
    //�ṹ��Ϊ�գ����СΪ��0 in c,1 in cpp
    struct st
    {
        char a; //1byte
        int b;  //4byte
        char c[5];  //5byte
        int* p; // 32λ�£�4byte 64λ�£�8byte
    };
    //
    union u
    {
        short a;    //2byte
        char b;     //1byte
        int c;      //4byte
        long long int d;    //8byte
        float* p;   //32λ�£�4byte 64λ�£�8byte
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
            s->~basic_string(); //��������������������ڴ�й©
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