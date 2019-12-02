#include "PF.h"
#include <iostream>
#include <string>

using namespace std;

void main()
{
    string s; string pf;//�������� ������ � �������� ����� 
    
    getline(std::cin, s);
    try
    {
        pf = PolF::PF(s);
        cout << endl << pf << endl;
        string* perem;//������ ���������
        double* zn;
        int count;
        PolF::ZN(pf, perem, zn, &count);
        cout << endl << PolF::Count(pf, perem, zn);
        delete[] zn;
        delete[] perem;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
}