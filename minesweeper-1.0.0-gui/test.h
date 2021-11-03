#pragma once
#include<iostream>
#include<crtdbg.h>
#include<iomanip>
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//onexit(_CrtDumpMemoryLeaks);
using std::cout;
using std::endl;

void output(vector<vector<int>>& v, int x, int y)
{
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            cout << std::left << std::setw(2) << v[i][j] << ' ';
        }
        cout << "\n";
    }
}