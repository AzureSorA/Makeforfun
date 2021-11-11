#include "mystring.h"

mystring::mystring()
{
    size_ = 0;
    data_ = new char[size_ + 1];
    if (data_ != nullptr)
    {
        data_[size_] = '\0';
    }
    else
    {
        std::abort();
    }
}

mystring::mystring(const char* s):data_(nullptr),size_(0)
{
    if (s != nullptr)
    {
        size_ = strlen(s);
        data_ = new char[size_ + 1];
        if (data_ != nullptr)
        {
            //strncpy_s(data_, size_ + 1, s, size_);
            for (int i = 0; i <= size_; ++i)
            {
                char c = *s++;
                data_[i] = c;
            }
        }
    }
}

mystring::mystring(const char* s,size_t count) :data_(nullptr), size_(0)
{
    if (s != nullptr)
    {
        size_ = count;
        data_ = new char[size_ + 1];
        if (data_ != nullptr)
        {
            for (size_t i = 0; i < count; ++i)
            {
                data_[i] = *s++;
            }
            data_[size_] = '\0';
        }
    }
}

mystring::mystring(const mystring& s) :data_(nullptr)
{
    mystring tmp(s.data_);
    std::swap(data_, tmp.data_);
    std::swap(size_, tmp.size_);
}

mystring::mystring(iterator first, iterator last)
{
    size_ = last - first;
    data_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = *first++;
    }
    data_[size_] = '\0';
}

mystring::mystring(const mystring& s,size_t pos,size_t count):data_(nullptr), size_(0)
{
    if (s.data_ != nullptr)
    {
        size_ = count;
        data_ = new char[size_ + 1];
        if (data_ != nullptr)
        {
            if (pos + count <= s.size_)
            {
                for (size_t i = 0, j = pos; i < count; ++i, ++j)
                {
                    data_[i] = s.data_[j];
                }
                data_[size_] = '\0';
            }
        }
    }
}

mystring::mystring(mystring&& s)noexcept:data_(nullptr), size_(0)
{
    if (this != &s)
    {
        data_ = s.data_;
        size_ = s.size_;
        s.data_ = nullptr;
    }
}

mystring::mystring(size_t count,char ch):size_(count)
{
    data_ = new char[count + 1];
    if (data_ != nullptr)
    {
        for (size_t i = 0; i < count; ++i)
        {
            data_[i] = ch;
        }
        data_[size_] = '\0';
    }
}

mystring::mystring(std::initializer_list<char> ilist) :data_(nullptr), size_(0)
{
    size_ = ilist.size();
    data_ = new char[size_ + 1];
    if (data_ != nullptr)
    {
        char* tmp = data_;
        for (auto i : ilist)
        {
            *tmp++ = i;
        }
        data_[size_] = '\0';
    }
}

mystring& mystring::operator=(char ch)
{
    size_ = 1;
    if (data_ != nullptr)
    {
        delete[] data_;
    }
    data_ = new char[size_ + 1];
    *data_ = ch;
    data_[size_] = '\0';
    return *this;
}

mystring& mystring::operator=(const char* s)
{
    if (s != nullptr)
    {
        size_ = strlen(s);
        if (data_ != nullptr)
        {
            delete[] data_;
        }
        data_ = new char[size_ + 1];
        for (int i = 0; i < size_; ++i)
        {
            data_[i] = *s++;
        }
        data_[size_] = '\0';
    }
    return *this;
}

mystring& mystring::operator=(const mystring& s)
{
    if (this != &s)
    {
        mystring tmp(s.data_);
        std::swap(data_, tmp.data_);
        std::swap(size_, tmp.size_);
    }
    return *this;
}

mystring& mystring::operator=(mystring&& s)noexcept
{
    if (this != &s)
    {
        if (data_ != nullptr)
        {
            delete[] data_;
        }
        data_ = s.data_;
        size_ = s.size_;
        s.data_ = nullptr;
        s.size_ = 0;
        return *this;
    }
    return *this;
}

mystring& mystring::operator=(std::initializer_list<char> ilist)
{
    mystring tmp(ilist);
    std::swap(data_, tmp.data_);
    std::swap(size_, tmp.size_);
    return *this;
}

mystring& mystring::assign(const char* s)
{
    if (s != nullptr)
    {
        size_ = strlen(s);
        if (data_ != nullptr)
        {
            delete[] data_;
        }
        data_ = new char[size_ + 1];
        for (int i = 0; i < size_; ++i)
        {
            data_[i] = *s++;
        }
        data_[size_] = '\0';
    }
    return *this;
}

mystring& mystring::assign(const char* s, size_t count)
{
    if (s != nullptr)
    {
        size_ = count;
        if (data_ != nullptr)
        {
            delete[] data_;
        }
        data_ = new char[size_ + 1];
        for (size_t i = 0; i < count; ++i)
        {
            data_[i] = *s++;
        }
        data_[size_] = '\0';
    }
    return *this;
}

mystring& mystring::assign(const mystring& s)
{
    if (data_ != nullptr)
    {
        delete[] data_;
        data_ = nullptr;
    }
    mystring tmp(s.data_);
    std::swap(data_, tmp.data_);
    std::swap(size_, tmp.size_);
    return *this;
}

mystring& mystring::assign(const mystring& s, size_t pos, size_t count)
{
    if (s.data_ != nullptr)
    {
        if (data_ != nullptr)
        {
            delete[] data_;
            data_ = nullptr;
        }
        size_ = count;
        data_ = new char[size_ + 1];
        if (data_ != nullptr)
        {
            if (pos + count <= s.size_)
            {
                for (size_t i = 0, j = pos; i < count; ++i, ++j)
                {
                    data_[i] = s.data_[j];
                }
                data_[size_] = '\0';
            }
        }
    }
    return *this;
}

mystring& mystring::assign(mystring&& s)
{
    if (this != &s)
    {
        size_ = strlen(s.data_);
        if (data_ != nullptr)
        {
            delete[] data_;
            data_ = nullptr;
        }
        data_ = s.data_;
        size_ = s.size_;
        s.data_ = nullptr;
        s.size_ = 0;
    }
    return *this;
}

mystring& mystring::assign(size_t count, char ch)
{
    size_ = count;
    if (data_ != nullptr)
    {
        delete[] data_;
    }
    data_ = new char[size_ + 1];
    for (size_t i = 0; i < count; ++i)
    {
        data_[i] = ch;
    }
    data_[size_] = '\0';
    return *this;
}

mystring& mystring::assign(std::initializer_list<char> ilist)
{
    if (data_ != nullptr)
    {
        delete[] data_;
    }
    size_ = ilist.size();
    data_ = new char[size_ + 1];
    char* tmp = data_;
    for (auto i : ilist)
    {
        *tmp++ = i;
    }
    data_[size_] = '\0';
    return *this;
}

mystring::~mystring()
{
    if (data_ != nullptr)
    {
        delete[] data_;
        data_ = nullptr;
    }
}

char& mystring::operator[](size_t pos)
{
    if (pos == size_)
    {
        return data_[size_];
    }
    return data_[pos];
}

char& mystring::at(size_t pos)
{
    if (pos >= size_)
        abort();
    return data_[pos];
}

char& mystring::front()
{
    if (size_ <= 0)
    {
        std::abort();
    }
    return data_[0];
}

char& mystring::back()
{
    if (size_ <= 0)
    {
        std::abort();
    }
    return data_[size_ - 1];
}

const char* mystring::data()const
{
    return data_;
}

const char* mystring::c_str()const
{
    return data_;
}

size_t mystring::size()const
{
    return size_;
}

size_t mystring::length()const
{
    return size_;
}

bool mystring::empty()const
{
    if (size_ == 0)
    {
        return true;
    }
    return false;
}

void mystring::clear()
{
    if (data_ != nullptr)
    {
        delete[] data_;
        data_ = new char[1];
        *data_ = '\0';
        size_ = 0;
    }
}

mystring& mystring::insert(char ch, size_t pos)
{
    if (pos <= size_)
    {
        size_ += 1;
        char* tmp = data_;
        char* old = data_;
        data_ = new char[size_ + 1];
        for (int i = 0; i < size_; ++i)
        {
            if (i == pos)
                data_[i] = ch;
            else
                data_[i] = *tmp++;
        }
        data_[size_] = '\0';
        delete[] old;
    }
    else
    {
        std::abort();
    }
    return *this;
}

mystring& mystring::insert(const char* s, size_t pos)
{
    if (pos <= size_)
    {
        size_ += strlen(s);
        char* tmp = data_;
        char* old = data_;
        data_ = new char[size_ + 1];
        for (int i = 0; i < size_; ++i)
        {
            if (i == pos)
            {
                while (*s != '\0')
                {
                    data_[i] = *s++;
                    ++i;
                }
            }
            else
                data_[i] = *tmp++;
        }
        data_[size_] = '\0';
        delete[] old;
    }
    else
    {
        std::abort();
    }
    return *this;
}

mystring& mystring::insert(const mystring& s, size_t pos)
{
    if (pos <= size_)
    {
        size_ += strlen(s.data_);
        char* tmp = data_;
        char* t = s.data_;
        char* old = data_;
        data_ = new char[size_ + 1];
        for (int i = 0; i < size_; ++i)
        {
            if (i == pos)
            {
                while (*t != '\0')
                {
                    data_[i] = *t++;
                    ++i;
                }
            }
            else
                data_[i] = *tmp++;
        }
        data_[size_] = '\0';
        delete[] old;
    }
    else
    {
        std::abort();
    }
    return *this;
}

mystring& mystring::erase(size_t pos, size_t count)
{
    if (pos + count < size_)
    {
        size_ -= count;
        char* tmp = data_;
        char* old = data_;
        data_ = new char[size_ + 1];
        for (int i = 0; i < size_;)
        {
            if (i == pos)
            {
                while (count > 0)
                    --count;
            }
            else
                data_[i++] = *tmp++;
        }
        delete[] old;
        data_[size_] = '\0';
    }
    else
    {
        std::abort();
    }
    return *this;
}

void mystring::push_back(char ch)
{
    insert(ch, size_);
}

void mystring::pop_back()
{
    if (size_ > 0)
    {
        --size_;
        data_[size_] = '\0';
    }
}

mystring& mystring::append(char ch)
{
    ++size_;
    char* tmp = data_;
    char* old = data_;
    data_ = new char[size_ + 1];
    for (int i = 0; i < size_-1; ++i)
    {
        data_[i] = *tmp++;
    }
    data_[size_ - 1] = ch;
    data_[size_] = '\0';
    return *this;
}

mystring& mystring::append(const char* s)
{
    char* tmp = data_;
    char* old = data_;
    size_t new_size = size_ + strlen(s);
    data_ = new char[new_size + 1];
    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = *tmp++;
    }
    for (size_t i = size_; i < new_size; ++i)
    {
        data_[i] = *s++;
    }
    size_ = new_size;
    data_[size_] = '\0';
    delete[] old;
    return *this;
}

mystring& mystring::append(const mystring& s)
{
    char* tmp = data_;
    char* t = s.data_;
    char* old = data_;
    size_t new_size = size_ + strlen(s.data_);
    data_ = new char[new_size + 1];
    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = *tmp++;
    }
    for (size_t i = size_; i < new_size; ++i)
    {
        data_[i] = *t++;
    }
    size_ = new_size;
    data_[size_] = '\0';
    delete[] old;
    return *this;
}

mystring& mystring::operator+=(char ch)
{
    return append(ch);
}

mystring& mystring::operator+=(const char* s)
{
    return append(s);
}

mystring& mystring::operator+=(const mystring& s)
{
    return append(s);
}

int mystring::compare(const char* s)const
{
    size_t lhs_sz = size();
    size_t rhs_sz = strlen(s);
    
    if (lhs_sz < rhs_sz)
        return -1;
    if (lhs_sz > rhs_sz)
        return 1;
    return 0;
}

int compares(const char* lhs, const char* rhs, const size_t range)
{
    for (size_t i = 0; i < range; ++i)
    {
        if (*lhs > *rhs)
        {
            return 1;
        }
        else if (*lhs < *rhs)
        {
            return -1;
        }
        ++lhs;
        ++rhs;
    }
    return 0;
}

int mystring::compare(const mystring& s)const
{
    size_t lhs_sz = size();
    size_t rhs_sz = strlen(s.data_);
    if (int result = compares(this->c_str(), s.c_str(), std::min(lhs_sz, rhs_sz)))
    {
        return result;
    }
    if (lhs_sz < rhs_sz)
        return -1;
    if (lhs_sz > rhs_sz)
        return 1;
    return 0;
}

mystring& mystring::replace(size_t pos, size_t count, const char* s)
{
    size_t sz = strlen(s);
    if (sz == count)
    {
        for (size_t i = pos; i < count; ++i)
        {
            data_[i] = *s++;
        }
    }
    else
    {
        size_t new_size = size_ - count + sz ;
        char* tmp = data_;
        char* old = data_;
        data_ = new char[new_size + 1];
        for (size_t i = 0; i < new_size; )
        {
            if (i == pos)
            {
                while (*s != '\0')
                {
                    data_[i++] = *s++;
                }
                tmp += count;
            }
            else
            {
                data_[i++] = *tmp++;
            }
        }
        delete[] old;
        size_ = new_size;
        data_[size_] = '\0';
    }
    return *this;
}

mystring mystring::substr(size_t pos, size_t count)
{
    mystring result;
    size_t range = pos + count;
    if (range > size_)
    {
        for (size_t i = pos; i < size_; ++i)
        {
            result += data_[i];
        }
    }
    else
    {
        for (size_t i = pos; i < range; ++i)
        {
            result += data_[i];
        }
    }
    return result;
}

int mystring::copy(char* dest, size_t pos, size_t count)
{
    size_t range = pos + count;
    if (range > size_)
    {
        for (size_t i = pos; i < size_; ++i)
        {
            *dest++ = data_[i];
        }
        return static_cast<int>(size_ - pos);
    }
    else
    {
        for (size_t i = pos; i < range; ++i)
        {
            *dest++ = data_[i];
        }
        return static_cast<int>(count);
    }
}

std::ostream& operator<<(std::ostream& os, const mystring& s)
{
    os << s.c_str();
    return os;
}

mystring operator+(mystring& lhs, mystring& rhs)
{
    return lhs += rhs;
    
}
mystring operator+(mystring& lhs, const char* s)
{
    return lhs += s;
}

mystring operator+(mystring& lhs, char ch)
{
    return lhs += ch;
}