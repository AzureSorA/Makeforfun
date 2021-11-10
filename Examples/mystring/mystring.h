#pragma once
#include<initializer_list>
#include<iostream>

//typedef unsigned int size_t;

class mystring
{
public:
    friend std::ostream& operator<<(std::ostream& os, const mystring& s);
    friend mystring operator+(mystring& lhs, mystring& rhs);
    friend mystring operator+(mystring& lhs, const char* s);
    friend mystring operator+(mystring& lhs, char ch);
    friend int compares(const char* lhs, const char* rhs,const size_t range);
    mystring();
    mystring(size_t size, char ch);
    mystring(const mystring& s, size_t pos, size_t count);
    mystring(const char* s, size_t count);
    mystring(const char* s);
    //mystring(iter,iter);
    mystring(const mystring& s);
    mystring(mystring&& s)noexcept;
    mystring(std::initializer_list<char> ilist);
    mystring& operator=(const mystring& s);
    mystring& operator=(mystring&& s)noexcept;
    mystring& operator=(const char* s);
    mystring& operator=(char ch);
    mystring& operator=(std::initializer_list<char> ilist);

    mystring& assign(size_t count, char ch);
    mystring& assign(const mystring& s);
    mystring& assign(const mystring& s,size_t pos,size_t count);
    mystring& assign(mystring&& s);
    mystring& assign(const char* s, size_t count);
    mystring& assign(const char* s);
    //mystring& mystring(iter,iter);
    mystring& assign(std::initializer_list<char> ilist);
    ~mystring();

    char& operator[](size_t pos);
    char& at(size_t pos);
    char& front();
    char& back();
    const char* data()const;
    const char* c_str()const;

    size_t size()const;
    size_t length()const;
    bool empty()const;

    void clear();
    mystring& insert(char ch, size_t pos);
    mystring& insert(const char* s, size_t pos);
    mystring& insert(const mystring& s, size_t pos);
    mystring& erase(size_t pos, size_t count);
    void push_back(char ch);
    void pop_back();
    mystring& append(char ch);
    mystring& append(const char* s);
    mystring& append(const mystring& s);
    mystring& operator+=(char ch);
    mystring& operator+=(const char* s);
    mystring& operator+=(const mystring& s);
    int compare(const mystring& s)const;
    int compare(const char* s)const;
    mystring& replace(size_t pos, size_t count, const char* s);

    mystring substr(size_t pos, size_t count);
    int copy(char* dest, size_t pos, size_t count);

private:
    char* data_;
    size_t size_;
};

