#include "PF.h"
#include <iostream>
#include <string>

using namespace std;

bool PolF::IsS(char zn)
{
    return ((zn == '+') || (zn == '-') || (zn == '*') || (zn == '/'));
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
        {
            cout << a[i] << " not a number ";
            return false;
        }
    return true;
}

bool PolF::IsPerem(string tmp, string* perem)
{
    for (int i = 0; i < 50; i++)
    {
        if (tmp == perem[i])
        {
            return true;
        }
    }
    return false;
}

double PolF::StToD(string a)
{
    double res = 0;
    for (int i = 0; i < a.length(); i++)
    {
        switch (a[i])
        {
        case '0':
            res += pow(10, (a.length() - i - 1)) * 0;
            break;
        case '1':
            res += pow(10, (a.length() - i - 1)) * 1;
            break;
        case '2':
            res += pow(10, (a.length() - i - 1)) * 2;
            break;
        case '3':
            res += pow(10, (a.length() - i - 1)) * 3;
            break;
        case '4':
            res += pow(10, (a.length() - i - 1)) * 4;
            break;
        case '5':
            res += pow(10, (a.length() - i - 1)) * 5;
            break;
        case '6':
            res += pow(10, (a.length() - i - 1)) * 6;
            break;
        case '7':
            res += pow(10, (a.length() - i - 1)) * 7;
            break;
        case '8':
            res += pow(10, (a.length() - i - 1)) * 8;
            break;
        case '9':
            res += pow(10, (a.length() - i - 1)) * 9;
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
    case '*': return 1;
    case '/': return 1;
    case '+': return 2;
    case '-': return 2;
    default: return 3;
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

string PolF::PF(string st, string* perem)
{
    if (st == "")
        throw "!empty line";
    string tmp = "", per = "";//тмп - входной элемент строки в форе, пер - переменная до знака
    int j = 0;//счетчик для массива переменных
    TStack<string> PF(50);
    string pf = "";//итоговая строка
    TStack<string> oper(50);
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
                    perem[j++] = per;
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
    try
    {
        if (per != "")
        {
            perem[j++] = per;
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
        pf += PF.Pop();
    }
    reverse(pf.begin(), pf.end());
    return pf;
}

int PolF::countof(string* perem)
{
    int i = 0;
    while (perem[i] != "")
        i++;
    return i;
}

void PolF::ZN(string* perem, double* zn)
{
    int flag = 0;
    for (int i = 0; i < countof(perem); i++)
    {
        if (IsD(perem[i]))
        {
            zn[i] = StToD(perem[i]);
            flag = 1;
        }
        else
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (perem[i] == perem[j])
                {
                    flag = 1;
                    zn[i] = zn[j];
                    break;
                }
            }
            if (flag == 0)
            {
                cout << perem[i] << " = ";
                cin >> zn[i];
                cout << endl;
            }
        }
        flag = 0;
    }
}

double PolF::Count(string PF, string* perem, double* zn)
{
    TStack<double> count(50);
    string tmp;
    double a, b;

    for (int i = 0; i < PF.length(); i++)
    {
        tmp += PF[i];
        if (IsPerem(tmp, perem) || (IsS(tmp[0])))
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

    }
    return count.Pop();
}