#include<iostream>
using std::cout;

//先定义一些tag
struct Base {};
struct Foo :Base {};

//假设有一个未知类
template<typename T>
struct unknown_type
{
    typedef T return_type;
};

//特性萃取器
template<typename unknown_type>
struct unknown_type_traits
{
    typedef typename unknown_type::return_type return_type;
};

//特性萃取器 —— 针对原生指针
template<typename T>
struct unknown_type_traits<T*>
{
    typedef T return_type;
};

//特性萃取其 —— 针对指向常数
template<typename T>
struct unknown_type_traits<const T*>
{
    typedef const T return_type;
};

//return_type 的构造函数
template<typename unknown_type>
inline typename unknown_type_traits<unknown_type>::return_type return_type(unknown_type)
{
    typedef typename unknown_type_traits<unknown_type>::return_type RT;
    return RT();
}

//决定使用哪一个类型
template<typename unknown_type>
inline typename unknown_type_traits<unknown_type>::return_type __func(unknown_type, Base)
{
    cout << "use Base flag\n";
    return Base();
}

template<typename unknown_type>
inline typename unknown_type_traits<unknown_type>::return_type __func(unknown_type, Foo)
{
    cout << "use Foo flag\n";
    return Foo();
}

template<typename unknown_type,typename T>
inline typename unknown_type_traits<unknown_type>::return_type __func(unknown_type, T)
{
    cout << "use origin ptr\n";
    return T();
}

//接口
template<typename unknown_type>
inline typename unknown_type_traits<unknown_type>::return_type func(unknown_type u)
{
    //typedef typename unknown_type_traits<unknown_type>::return_type return_type;
    return __func(u, return_type(u));
}


int main()
{
    unknown_type<Base> a;
    unknown_type<Foo> b;
    int value = 1;
    int* p = &value;
    Base v1 = func(a);
    cout << typeid(func(a)).name() << "\n";
    Foo v2 = func(b);
    int v3 = func(p);
}