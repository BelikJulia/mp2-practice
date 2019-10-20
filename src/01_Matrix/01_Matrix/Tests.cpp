#include <iostream>
#include "Tests.h"
using namespace std;

void Tests1() 
{
    cout << "TEST 1" << endl << "A + B" << endl;
    int n;
    cout << "Size A = ";
    cin >> n;
    TMatrix<double> A(n);
    cout << "A = " << endl;
    cin >> A; cout << A;

    cout << "Size B = ";
    cin >> n;
    TMatrix<double> B(n);
    cout << "B = " << endl;
    cin >> B;
    cout << "A + B" << endl;
    TMatrix<double> C(n);
    try
    {
        C = A + B;
        cout << C;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << "Test 1 passed" << endl << endl;
}

void Tests2()
{
    cout << "TEST 2" << endl << "A - B" << endl;
    int n;
    cout << "Size A = ";
    cin >> n;
    TMatrix<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "Size B = ";
    cin >> n;
    TMatrix<double> B(n);
    cout << "B = " << endl;
    cin >> B;

    cout << "A - B" << endl;
    TMatrix<double> C(n);
    try
    {
        C = A - B;
        cout << C;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << "Test 2 passed" << endl << endl;
}

void Tests3()
{
    cout << "TEST 3" << endl << "A * B" << endl;
    int n;
    cout << "Size A = ";
    cin >> n;
    TMatrix<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "Size B = ";
    cin >> n;
    TMatrix<double> B(n);
    cout << "B = " << endl;
    cin >> B;

    cout << "A * B" << endl;
    TMatrix<double> C(n);
    try
    {
        C = A * B;
        cout << C;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << "Test 3 passed" << endl << endl;
}

void Tests4()
{
    cout << "TEST 4" << endl << "A + const" << endl;
    int n;
    cout << "Size A = ";
    cin >> n;
    TMatrix<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "Const = ";
    double c;
    cin >> c;

    cout << "A + const" << endl;
    TMatrix<double> C(n);
    C = A + c;
    cout << C;
    cout << "Test 4 passed" << endl << endl;
}

void Tests5()
{
    cout << "TEST 5" << endl << "A - const" << endl;
    int n;
    cout << "Size A = ";
    cin >> n;
    TMatrix<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "Const = ";
    double c;
    cin >> c;

    cout << "A - const" << endl;
    TMatrix<double> C(n);
    C = A - c;
    cout << C;
    cout << "Test 5 passed" << endl << endl;
}

void Tests6()
{
    cout << "TEST 6" << endl << "A * const" << endl;
    int n;
    cout << "Size A = ";
    cin >> n;
    TMatrix<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "Const = ";
    double c;
    cin >> c;

    cout << "A * const" << endl;
    TMatrix<double> C(n);
    C = A * c;
    cout << C;
    cout << "Test 6 passed" << endl << endl;
}

void Tests7()
{
    cout << "TEST 7" << endl << "A * vec" << endl;
    int n;
    cout << "Size A = ";
    cin >> n;
    TMatrix<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "Size vec = ";
    cin >> n;
    TVector<double> v(n);
    cout << "B = " << endl;
    cin >> v;

    cout << "A * vec" << endl;
    TVector<double> C(n);
    try
    {
        C = A * v;
        cout << C;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << "Test 7 passed" << endl << endl;
}

void Tests8()
{
    cout << "TEST 8" << endl << "A == B" << endl;
    int n;
    cout << "Size A = ";
    cin >> n;
    TMatrix<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "Size B = ";
    cin >> n;
    TMatrix<double> B(n);
    cout << "B = " << endl;
    cin >> B;

    try
    {
        if (A == B)
            cout << "A = B" << endl;
        else
            cout << "A != B" << endl;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << "Test 8 passed" << endl << endl;
}

void Tests9()
{
    cout << "TEST 9" << endl << "A != B" << endl;
    int n;
    cout << "Size A = ";
    cin >> n;
    TMatrix<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "Size B = ";
    cin >> n;
    TMatrix<double> B(n);
    cout << "B = " << endl;
    cin >> B;

    try
    {
        if (A != B)
            cout << "A != B" << endl;
        else
            cout << "A = B" << endl;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << "Test 9 passed" << endl << endl;
}

void Tests10()
{
    cout << "TEST 1" << endl << "A + B" << endl;
    int n;
    cout << "Size A = ";
    cin >> n;
    TMatrix<double> A(n);
    cout << "A = " << endl;
    cin >> A;
    TMatrix<double> B(A);
    cout << B;
}