#include "PF.h"
#include <iostream>
#include <string>

using namespace std;

void main()
{
    string s, pf;//�������� ������ � �������� ����� 
    string* perem = new string[50]{ "" };//������ ���������
    double* zn = new double[50];
    cin >> s;
    try
    {
        pf = PolF::PF(s, perem);
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << endl << pf << endl;
    PolF::ZN(perem, zn);
    cout << endl << PolF::Count(pf, perem, zn);
    cin >> s;
}