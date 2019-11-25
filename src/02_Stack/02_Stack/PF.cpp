#include "PF.h"
#include <iostream>
#include <string>
using namespace std;

bool PolF::IsS(char zn)
{
    return ((zn == '+') || (zn == '-') || (zn == '*') || (zn == '/'));
}

bool PolF::IsCorrect(string st)
{
    int a = 0;
    int b = 0;
    for (int i = 0; i < st.length(); i++)
    {
        if (st[i] == '(')
            a++;
        if (st[i] == ')')
            b++;
        if (b > a)
            return false;
    }
    if (a != b)
        return false;
    return true;
}

double PolF::DO(string tmp, double a, double b)
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

bool PolF::IsD(string a)
{
    for (int i = 0; i < a.length(); i++)
        if ((a[i] != '0') && (a[i] != '1') && (a[i] != '2') && (a[i] != '3') && (a[i] != '4') &&
            (a[i] != '5') && (a[i] != '6') && (a[i] != '7') && (a[i] != '8') && (a[i] != '9') && (a[i] != ' '))
            return false;
    return true;
}

double PolF::StToD(string a)
{
    double res = 0;
    for (int i = 0; i < a.length(); i++)
    {
        double s = 1;
        for (int j = 1; j < a.length() - i; j++)
            s *= 10;
        switch (a[i])
        {
        case '0':
            res += s * 0;
            break;
        case '1':
            res += s * 1;
            break;
        case '2':
            res += s * 2;
            break;
        case '3':
            res += s * 3;
            break;
        case '4':
            res += s * 4;
            break;
        case '5':
            res += s * 5;
            break;
        case '6':
            res += s * 6;
            break;
        case '7':
            res += s * 7;
            break;
        case '8':
            res += s * 8;
            break;
        case '9':
            res += s * 9;
            break;
        default:
            break;
        }
    }
    return res;
}

double PolF::znach(string a, string* perem, double* zn)
{
    for (int i = 0; i < 50; i++)
    {
        if (a == perem[i])
        {
            return zn[i];
        }
    }
    return 0;
}

int PolF::Prior(string s)
{
    switch (s[0])
    {
    case '*': return 2;
    case '/': return 1;
    case '+': return 4;
    case '-': return 3;
    default: return 5;
    }
}

void PolF::Sign(string tmp, TStack<string>& s, TStack<string>& gl)
{
    string st;
    TStack<string> oper(50);
    if (!(s.IsEmpty()))
    {
        do
        {
            try
            {
                st = s.Pop();
            }
            catch (const char* er)
            {
                cout << er << " in Sign f in do " << endl;
            }
            if (Prior(st) < Prior(tmp))
            {
                oper.Push(st);
            }
            else
            {
                s.Push(st);
                s.Push(tmp);
            }
            try
            {
                if (!(s.IsEmpty()))
                {
                    st = s.Pop();
                    s.Push(st);
                }
            }
            catch (const char* er)
            {
                cout << er << " in Sign f " << endl;
            }
        } while ((Prior(st) < Prior(tmp)) && (!(s.IsEmpty())));
        if (!(oper.IsEmpty()))
        {
            s.Push(tmp);
            do
            {
                gl.Push(oper.Pop());
            } while (!(oper.IsEmpty()));
        }
    }
    else
    {
        s.Push(tmp);
    }
}

string PolF::PF(string st)
{
    if (st == "")
        throw "!empty line";
    if (!(IsCorrect(st)))
        throw "!invalid line";
    string tmp = "", per = "";//тмп - входной элемент строки в форе, пер - переменная до знака
    int j = 0;//счетчик для массива переменных
    TStack<string> PF(50);
    string pf = "";//итоговая строка
    TStack<string> oper(50);
    for (int i = 0; i < st.length(); i++)
    {
        tmp = st[i];
        if (tmp != " ")
        {
            if (IsS(st[i]) || (st[i] == '('))
            {
                try
                {
                    if (per != "")
                    {
                        reverse(per.begin(), per.end());
                        PF.Push(per);
                        per = "";
                    }
                }
                catch (const char* er)
                {
                    cout << er << " in Sign " << endl;
                }
                try
                {
                    if ((tmp != "(") && (!(oper.IsEmpty())))
                    {
                        Sign(tmp, oper, PF);
                    }
                    else
                    {
                        oper.Push(tmp);
                    }
                }
                catch (const char* er)
                {
                    cout << er << " in oper" << endl;
                }
            }
            else if (st[i] == ')')
            {
                string z = oper.Pop();
                try
                {
                    if (per != "")
                    {
                        reverse(per.begin(), per.end());
                        PF.Push(per);
                        per = "";
                    }
                }
                catch (const char* er)
                {
                    cout << er << endl;
                }
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
                } while (z != "(");
            }
            else
            {
                per += tmp;
            }
        }
    }
    try
    {
        if (per != "")
        {
            reverse(per.begin(), per.end());
            PF.Push(per);
            per = "";
        }
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    string z;
    do
    {
        try
        {
            z = oper.Pop();
        }
        catch (const char* er)
        {
            cout << er << " in end  in do " << endl;
        }
        try
        {
            PF.Push(z);
        }
        catch (const char* er)
        {
            cout << er << " in Push in end " << endl;
        }
    } while (!(oper.IsEmpty()));
    while (!(PF.IsEmpty()))
    {
        pf += (" " + PF.Pop());
    }
    reverse(pf.begin(), pf.end());
    return pf;
}

void PolF::ZN(string PF, string*& perem, double*& zn, int* count)
{
    string tmp = "";
    int flag = 0;
    int p = 0;
    for (int i = 0; i < PF.length(); i++)
    {
        if (PF[i] != ' ')
        {
            tmp += PF[i];
        }
        else
        {
            if (!(IsS(tmp[0])))
                p++;
            tmp = "";
        }
    }
    tmp = "";
    perem = new string[p]; 
    for (int i = 0; i < p; i++)
        perem[i] = "";
    zn = new double[p]; 
    p = 0;
    for (int i = 0; i < PF.length(); i++)
    {
        if (PF[i] != ' ')
            tmp += PF[i];
        else
        {
            if (!(IsS(tmp[0])))
            {
                flag = 0;
                for (int j = (p - 1); j >= 0; j--)
                {
                    if (tmp == perem[j])
                    {
                        flag = 1;
                    }
                }
                if (flag == 0)
                {
                    if (IsD(tmp))
                    {
                        perem[p] = tmp;
                        zn[p++] = StToD(tmp);
                    }
                    else
                    {
                        perem[p] = tmp;
                        cout << perem[p] << " = ";
                        cin >> zn[p++];
                        cout << endl;
                    }
                }
            }
            tmp = "";
        }
    }
    *count = p;
}

double PolF::Count(string PF, string* perem, double* zn)
{
    TStack<double> count(50);
    string tmp, tmp1;
    double a, b;

    for (int i = 0; i < PF.length(); i++)
    {
        tmp1 = PF[i];
        if (tmp1 == " ")
        {
            if (IsS(tmp[0]))
            {
                b = count.Pop();
                a = count.Pop();
                count.Push(DO(tmp, a, b));
            }
            else
                count.Push(znach(tmp, perem, zn));
            tmp = "";
        }
        else
            tmp += tmp1;
    }
    return count.Pop();
}