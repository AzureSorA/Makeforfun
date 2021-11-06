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