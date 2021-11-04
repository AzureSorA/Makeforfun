#include<iostream>
#include<vector>
#include<deque>
#include<iomanip>
#include<string>
#include<random>

using std::string;
using std::deque;
using std::vector;
using std::cout;
using std::endl;

struct position
{
    int x;
    int y;
};

int flag = 1;

void init(vector<vector<int>>& t, int x, int y)
{
    vector<vector<int>>().swap(t);
    for (int i = 0; i < x; ++i)
    {
        vector<int> temp;
        for (int j = 0; j < y; ++j)
        {
            temp.push_back(-1);
        }
        t.push_back(temp);
    }
}

void print(vector<vector<int>>& t, int x, int y)
{
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            std::cout << std::left << std::setw(3) << t[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void display(vector<vector<int>>& t, vector<vector<int>>& s, int x, int y)
{
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            if (t[i][j] >= 0)s[i][j] = t[i][j];
            std::cout << std::left << std::setw(3) << s[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void set_mines(vector<vector<int>>& t)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 8);
    int x(0), y(0);
    for (int i = 0; i < 10; ++i)
    {
        x = dis(gen);
        y = dis(gen);
        if (t[x][y] != -3 && t[x][y] < 0)
        {
            t[x][y] = -3;
        }
        else if (t[x][y] == -3)
        {
            while (1)
            {
                x = dis(gen);
                y = dis(gen);
                if (t[x][y] != -3 && t[x][y] < 0)
                {
                    t[x][y] = -3;
                    break;
                }
            }
        }
    }
}

bool exisit(deque<position>& q, int x, int y)
{
    for (int i = 0; i < q.size(); ++i)
    {
        if (q[i].x == x && q[i].y == y)
        {
            return true;
        }
    }
    return false;
}

void check(vector<vector<int>>& t,int x,int y)
{
    if (t[x][y] == -3)
    {
        cout << "you click the mine,you are lose.\n";
        flag = 0;
        return;
    }
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            if (t[x][y] == -1)return;
        }
    }
    flag = 1;
}

void play(vector<vector<int>>& t, int x, int y)
{
    check(t, x, y);
    int max_x = t.size() - 1;
    int max_y = t[x].size() - 1;
    deque<position> q;
    position f(x, y);
    q.push_back(f);
    int count = 0;
    while (!q.empty())
    {
        position temp = q.back();
        q.pop_back();
        int mines = 0;
        int numbers = 0;
        for (int dx = (temp.x > 0 ? -1 : 0); dx <= (temp.x < max_x ? 1 : 0); ++dx)
        {
            for (int dy = (temp.y > 0 ? -1 : 0); dy <= (temp.y < max_y ? 1 : 0); ++dy)
            {
                if (dx != 0 || dy != 0)
                {
                    if (t[temp.x + dx][temp.y + dy] == -1 || t[temp.x + dx][temp.y + dy] == -2)
                    {
                        if (!exisit(q, temp.x + dx, temp.y + dy))
                        {
                            ++numbers;
                            q.push_back({ temp.x + dx ,temp.y + dy });
                        }
                    }
                    else if (t[temp.x + dx][temp.y + dy] == -3 || t[temp.x + dx][temp.y + dy] == -4)
                    {
                        ++mines;
                    }
                }
            }
        }
        t[temp.x][temp.y] = mines;
        if (mines != 0)
        {
            while (numbers > 0)
            {
                position temp = q.back();
                q.pop_back();
                --numbers;
            }
        }
    }
}

int main()
{
    vector<vector<int>> t;
    init(t, 9, 9);
    vector<vector<int>> show(t);
    set_mines(t);
    int x(0), y(0);
    while (flag)
    {
        display(t, show, 9, 9);
        cout << "input position x,y: ";
        std::cin >> x >> y;
        std::cout << "\n";
        if (x <= 8 && x >= 0 && y <= 8 && y >= 0)
        {
            play(t, x, y);
        }
        else
        {
            cout << "out of range,please try a again !!!\n";
        }
    }
    return 0;
}