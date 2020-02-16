#include <iostream>
#include "Tests.h"
#include <string>
using namespace std;

void Test1()
{
    string st;
    cout << "Polynom = ";
    cin >> st;
    try
    {
        TPolynom a(st);
        cout << a << endl;
    }
    catch (char* er)
    {
        cout << er;
    }
    cout << "Test 1 passed";
    cin >> st;
}