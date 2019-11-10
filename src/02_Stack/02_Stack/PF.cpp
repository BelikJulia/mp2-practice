#include "PF.h"
#include <iostream>
#include <cstring>

using namespace std;

bool IsS(char zn)
{
    return ((zn == '+') || (zn == '-') || (zn == '*') || (zn == '/'));
}

double DO(string tmp, double a, double b)
{
    switch (tmp[0])
    {
    case '*': return a * b;
    case '/': return a / b;
    case '+': return a + b;
    case '-': return a - b;
    default: return 0;
    }
}

void SpaceRemoval(string& tmp)
{
    for (int i = 0; i < tmp.length(); i++)
    {
        if (tmp[i] == ' ')
        {
            for (int j = i; tmp[j] != '/n'; j++)
                tmp[j] = tmp[j + 1];
        }
    }
}

double PolF::znach(string a)
{
    for (int i = 0; i < sizeperem; i++)
    {
        if (a == perem[i])
            return zn[i];
    }
    return 0;
}

int Prior(string s)
{
    switch (s[0])
    {
    case '*': return 1;
    case '/': return 1;
    case '+': return 2;
    case '-': return 2;
    default: return 3;
    }
}

void Sign(string tmp, TStack<string>& s)
{
    string st = s.Pop();
    if (Prior(st) < Prior(tmp))
    {
        s.Push(st);
        s.Push(tmp);
    }
    else
    {
        s.Push(st);
        s.Push(tmp);
    }
};

PolF::PolF(string st)
{
    if (st == "")
        throw "!empty line";
    SpaceRemoval(st);
    string tmp = "", per = "";
    int j = 0;
    sizeperem = 0;
    perem = new string[st.length()];
    zn = new double[st.length()];
    PF = TStack<string>(st.length());
    TStack<string> oper(st.length());
    for (int i = 0; i < st.length(); i++)
    {
        tmp = st[i];
        if (IsS(st[i]) || (st[i] == '('))
        {
            try
            {
                if (per != "")
                {
                    perem[j++] = per;
                    PF.Push(per);
                    sizeperem++;
                }
            }
            catch (const char* er)
            {
                cout << er << endl;
            }
            try
            {
                if (tmp != "(")
                    Sign(tmp, oper);
                else
                    oper.Push(tmp);
            }
            catch (const char* er)
            {
                cout << er << endl;
            }
        }
        else if (st[i] == ')')
        {
            string z = oper.Pop();
            do
            {
                try
                {
                    if (per != "")
                    {
                        perem[j++] = per;
                        PF.Push(per);
                    }
                }
                catch (const char* er)
                {
                    cout << er << endl;
                }
                try
                {
                    PF.Push(z);
                }
                catch (const char* er)
                {
                    cout << er << endl;
                }
                try
                {
                    z = oper.Pop();
                }
                catch (const char* er)
                {
                    cout << er << endl;
                }
            } while (z != "(");
        }
        else
            per += tmp;
    }
    oper.Push("0");
    string z = oper.Pop();
    do
    {
        try
        {
            PF.Push(z);
        }
        catch (const char* er)
        {
            cout << er << endl;
        }
        try
        {
            z = oper.Pop();
        }
        catch (const char* er)
        {
            cout << er << endl;
        }
    } while (z != "0");
}

PolF::~PolF()
{
    delete perem;
    delete zn;
    sizeperem = 0;
}

void PolF::PrintPF()
{
    cout << PF << endl;
}

void PolF::ZN()
{
    for (int i = 0; i < sizeperem; i++)
    {
        cout << perem[i] << " = ";
        cin >> zn[i];
        cout << endl;
    }
}

double PolF::Count()
{
    TStack<string> res(50);
    TStack<double> count(50);
    string tmp;
    double a, b;
    for (int i = 0; i < PF.GetSize(); i++)
        res.Push(PF.Pop());
    for (int i = 0; i < PF.GetSize(); i++)
    {
        tmp = res.Pop();
        if (IsS(tmp[0]))
        {
            a = count.Pop();
            b = count.Pop();
            count.Push(DO(tmp, a, b));
        }
        else
            count.Push(znach(tmp));
    }
    return count.Pop();
}