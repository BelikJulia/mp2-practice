#pragma once
#include "Stack.h"
#include <iostream>

using namespace std;

class PolF
{
private:
    TStack<string> PF;
    string* perem;
    double* zn;
    int sizeperem;
public:
    PolF(string st = NULL);
    ~PolF();
    void PrintPF();//����� �������� �����
    void ZN();//���� �������� ����������
    double Count();//������� ��������
    double znach(string a);
};

void SpaceRemoval(string& tmp);
bool IsS(char zn);
