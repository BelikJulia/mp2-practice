#include <iostream>
#include "Tests.h"
#include <string>
using namespace std;

void Test1()
{
    string st = "26x^3y^7z^9+2y^8-3x^6+5";
    cout << "Polynom " << endl;
    cin >> st;
    try
    {
        TPolynom a(st);
        TPolynom b;
        b = -a;
        cout << "-a = b = "<< b << endl;
    }
    catch (char* er)
    {
        cout << er;
    }
    cout << "Test 1 passed" << endl << endl;
    cin >> st;
}

void Test2()
{
    string st = "26x^3y^7z^9+2y^8-3x^6";
    cout << "Polynom = ";
    cin >> st;
    try
    {
        TPolynom a(st);
        cout << "a = "<< a << endl;
        st = "-26x^3y^7z^9+235";
        cin >> st;
        TPolynom b(st);
        cout << "b = " << b << endl;
        TPolynom c; 
        c = a + b;
        cout << "a + b = " << c << endl;
    }
    catch (char* er)
    {
        cout << er;
    }
    cout << "Test 2 passed" << endl << endl;
    //cin >> st;
}

void Test3()
{
    string st = "26x^3y^7z^9+2y^8-3x^6";
    cout << "Polynom = ";
    cin >> st;
    try
    {
        TPolynom a(st);
        cout <<"a = " << a << endl;
        st = "-26x^3y^7z^9+235";
        cin >> st;
        TPolynom b(st);
        cout <<"b = " << b << endl;
        TPolynom c;
        c = a - b;
        cout << "a - b = " << c << endl;
    }
    catch (char* er)
    {
        cout << er;
    }
    cout << "Test 3 passed" << endl << endl;
    //cin >> st;
}

void Test4()
{
    string st = "26x^3y^2z^2+2y^3-3x^4";
    cout << "Polynom = ";
    cin >> st;
    try
    {
        TPolynom a(st);
        cout << "a = " <<a << endl;
        st = "-26x^2y^2+5";
        cin >> st;
        TPolynom b(st);
        cout << "b = " << b << endl;
        TPolynom c;
        c = a * b;
        cout << "a * b = " << c << endl;
    }
    catch (char* er)
    {
        cout << er;
    }
    cout << "Test 4 passed" << endl << endl;
    //cin >> st;
}

void Test5()
{
    TNode<unsigned int, double> a = TNode<unsigned int, double>(23, 46, NULL);
    string st = "26x^3y^2z^2+2y^3-3x^4";
    TPolynom b(st);
    TPolynom c;
    c = b * a;
    cout << a << " * " << b << " = " << c << endl;
    cout << "Test 5 passed" << endl << endl;
    int i;
    cin >> i;
}