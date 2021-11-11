#include "mystring.h"
#include "gtest/gtest.h"

TEST(mystring, Constructor)
{
    mystring tmp("hello");
    mystring s;
    EXPECT_STREQ("", s.c_str());
    mystring s1("hello");
    EXPECT_STREQ("hello", s1.c_str());
    mystring s2(s1);
    EXPECT_STREQ("hello", s2.c_str());
    mystring s3(s2, 0, s2.size());
    EXPECT_STREQ("hello", s3.c_str());
    mystring s4(std::move(tmp));
    EXPECT_STREQ("hello", s4.c_str());
    mystring s5(5, 'a');
    EXPECT_STREQ("aaaaa", s5.c_str());
    mystring s6({ 'h','e','l','l','o' });
    EXPECT_STREQ("hello", s6.c_str());
    mystring s7(s6.begin(), s6.end());
    EXPECT_STREQ("hello", s7.c_str());
}

TEST(mystring, AssignFunction)
{
    mystring s8;
    s8.assign("hello");
    EXPECT_STREQ("hello", s8.c_str());
    s8.assign("hello", 3);
    EXPECT_STREQ("hel", s8.c_str());
    s8.assign(5, 'h');
    EXPECT_STREQ("hhhhh", s8.c_str());
    s8.assign({ 'h','e','l','l','o' });
    EXPECT_STREQ("hello", s8.c_str());
    mystring t1("hello");
    s8.assign(t1);
    EXPECT_STREQ("hello", s8.c_str());
    s8.assign(t1, 0, t1.size());
    EXPECT_STREQ("hello", s8.c_str());
    s8.assign(std::move(t1));
    EXPECT_STREQ("hello", s8.c_str());
}

TEST(mystring, Operator)
{
    mystring t("hello");
    mystring s7;
    s7 = 'h';
    EXPECT_STREQ("h", s7.c_str());
    s7 = "hello";
    EXPECT_STREQ("hello", s7.c_str());
    s7 = t;
    EXPECT_STREQ("hello", s7.c_str());
    s7 = std::move(t);
    EXPECT_STREQ("hello", s7.c_str());
    s7 = { 'h','e','l','l','o' };
    EXPECT_STREQ("hello", s7.c_str());
}

TEST(mystring, Operation)
{
    //insert clear push pop
    mystring s("hello");
    s.insert('w', 0);
    s.insert('w', 5);
    EXPECT_STREQ("whellwo", s.c_str());
    s.clear();
    s.insert("hello", 0);
    EXPECT_STREQ("hello", s.c_str());
    mystring s1("world");
    s.insert(s1, 5);
    EXPECT_STREQ("helloworld", s.c_str());
    s.push_back('e');
    EXPECT_STREQ("helloworlde", s.c_str());
    s.pop_back();
    s.pop_back();
    EXPECT_STREQ("helloworl", s.c_str());
}

TEST(mystring, AppendFunction)
{
    mystring s;
    s.append('h');
    EXPECT_STREQ("h", s.c_str());
    s.append("ello");
    EXPECT_STREQ("hello", s.c_str());
    mystring s1("world");
    s.append(s1);
    EXPECT_STREQ("helloworld", s.c_str());
    s += "apple";
    EXPECT_STREQ("helloworldapple", s.c_str());
    s += s;
    EXPECT_STREQ("helloworldapplehelloworldapple", s.c_str());
    s += 'z';
    EXPECT_STREQ("helloworldapplehelloworldapplez", s.c_str());
    EXPECT_STREQ("worldapple", s.substr(5, 10).c_str());
    mystring s5("hello");
    mystring s2("hel");
    mystring s3("hellozzll");
    mystring s4("hello");
    EXPECT_EQ(1, s5.compare(s2));
    EXPECT_EQ(-1, s5.compare(s3));
    EXPECT_EQ(0, s5.compare(s4));
    char test[6] = {};
    s.copy(test, 0, 5);
    EXPECT_STREQ("hello", test);

    mystring s6("hello");
    s6.replace(0, 4, "world");
    EXPECT_STREQ("worldo", s6.c_str());
}

TEST(mystring, Iterator)
{
    mystring s("hello");
    mystring s1(s.begin(), s.end());
    EXPECT_STREQ("hello", s1.c_str());
}