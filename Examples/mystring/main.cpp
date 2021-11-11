#include"mystring.h"
using std::cout;

int main()
{
    std::string c("hello");
    cout << c << "\n";
    cout<<sizeof(c.c_str())<<'\n';
    c.pop_back();
    cout << c << "\n";
    cout << sizeof(c.c_str()) << '\n';
    //constructor
    mystring tmp("hello");
    mystring s;
    mystring s1("hello");
    mystring s2(s1);
    mystring s3(s2, 0, s2.size());
    mystring s4(std::move(tmp));
    mystring s5(5, 'a');
    mystring s6({ 'h','e','l','l','o' });
    cout << s << "\n";
    cout << s1 << "\n";
    cout << s2 << "\n";
    cout << s3 << "\n";
    cout << s4 << "\n";
    cout << s5 << "\n";
    cout << s6 << "\n";
    //operator=
    mystring t("hello");
    mystring s7;
    s7 = 'h';
    cout << s7 << "\n";
    s7 = "hello";
    cout << s7 << "\n";
    s7 = s3;
    cout << s7 << "\n";
    s7 = std::move(t);
    cout << s7 << "\n";
    s7 = { 'h','e','l','l','o' };
    cout << s7 << "\n";

    //assign
    cout << "\n";
    mystring s8;
    s8.assign("hello");
    cout << s8 << "\n";
    s8.assign("hello", 3);
    cout << s8 << "\n";
    s8.assign(5, 'h');
    cout << s8 << "\n";
    s8.assign({ 'h','e','l','l','o' });
    cout << s8 << "\n";
    mystring t1("hello");
    s8.assign(t1);
    cout << s8 << "\n";
    s8.assign(t1, 0, t1.size());
    cout << s8 << "\n";
    s8.assign(std::move(t1));
    cout << s8 << "\n";

    {
        mystring s("hello");
        s.insert('w', 0);
        s.insert('w', 5);
        cout << s << "\n";
        s.clear();
        s.insert("hello", 0);
        cout << s << "\n";
        mystring s1("world");
        s.insert(s1, 5);
        cout << s << "\n";
        s.push_back('e');
        cout << s << "\n";
        s.pop_back();
        s.pop_back();
        cout << s << "\n";
    }

    {
        cout << "\n";
        mystring s;
        s.append('h');
        cout << s << "\n";
        s.append("ello");
        cout << s << "\n";
        mystring s1("world");
        s.append(s1);
        cout << s << "\n";
        s += "apple";
        cout << s << "\n";
        s += s;
        cout << s << "\n";
        s += 'z';
        cout << s << "\n";
        cout << s.substr(5, 10) << "\n";
        mystring s5("hello");
        mystring s2("hel");
        mystring s3("hellozzll");
        mystring s4("hello");
        cout<<s5.compare(s2)<<"\n";
        cout << s5.compare(s3)<<"\n";
        cout << s5.compare(s4)<<"\n";
        char test[6] = {};
        s.copy(test, 0, 5);
        cout << test << "\n";

        mystring s6("hello");
        s6.replace(0, 4, "world");
        cout << s6 << "\n";
    }
    {
        mystring s("hello");
        for (mystring::iterator it = s.begin(); it != s.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << '\n';
        mystring s1(s.begin(), s.end());
        cout << s1 << '\n';
    }
    onexit(_CrtDumpMemoryLeaks);
    return 0;
}