#pragma once
#include "Stack.h"
#include <iostream>

using namespace std;

class PolF
{
private:
    static bool IsS(char zn);
    static double DO(string tmp, double a, double b);
    static int Prior(string s);
    static double znach(string a, string* perem, double* zn);//значение переменной а
    static void Sign(string tmp, TStack<string>& s, TStack<string>& gl);
    static int countof(string* perem);
    static bool IsD(string a);
    static double StToD(string a);
    static bool IsPerem(string tmp, string* perem);
    static bool IsCorrect(string st);
public:
    static string PF(string st, string* perem);
    static void ZN(string* perem, double* zn);//ввод значений переменных
    static double Count(string PF, string* perem, double* zn);//подсчет значения
};