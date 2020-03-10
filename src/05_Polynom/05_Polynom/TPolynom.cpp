#include "TPolynom.h"
#include <iostream>
#include <string>

using namespace std;

TPolynom::TPolynom()
{
    pol = new TList<unsigned int, double>();
}
TPolynom::TPolynom(const TList<unsigned int, double>* tm)
{
    CheckLim(tm);
    pol = new TList<unsigned int, double>(*tm);
}
TPolynom::TPolynom(const string& st)
{
    if (st == "")
        throw "!empty line";
    pol = new TList<unsigned int, double>();
    string tmp = "";
    string powerst = "";
    char sign = '+';
    char nowis = ' ';
    unsigned int power = 0;
    double num = 0;
    int i = 0;
    TMonom rez;
    rez.pNext = NULL;
    while (i < st.length())
    {
        if (st[i] != ' ')
        {
            switch (st[i])
            {
            case 'x':
                power += 100;
                nowis = 'x';
                break;
            case 'y':
                power += 10;
                nowis = 'y';
                break;
            case 'z':
                power += 1;
                nowis = 'z';
                break;
            case '+':
                if ((tmp == "") && (power != 0))
                    num = 1;
                else if (tmp != "")
                    num = stoi(tmp);
                if (sign == '-')
                    num *= (-1);
                rez.key = power;
                rez.pData = num;
                InsertInSort(rez);
                power = 0;
                num = 0; 
                tmp = "";
                sign = '+';
                break;
            case '-':
                if ((tmp == "") && (power != 0))
                    num = 1;
                else if (tmp != "")
                    num = stoi(tmp);
                if (sign == '-')
                    num *= (-1);
                rez.key = power;
                rez.pData = num;
                InsertInSort(rez);
                power = 0;
                num = 0;
                tmp = "";
                sign = '-';
                break;
            case '*':
                break;
            case '^':
                i++;
                powerst += st[i];
                switch (nowis)
                {
                case 'x':
                    power += (stoi(powerst) - 1) * 100;
                    break;
                case 'y':
                    power += (stoi(powerst) - 1) * 10;
                    break;
                case 'z':
                    power += stoi(powerst) - 1;
                    break;
                }
                powerst = st[i + 1];
                if (IsDouble(powerst))
                    throw "limit power";
                else
                    powerst = "";
                break;
            default:
                tmp += st[i];
                break;
            }
        }
        i++;
    }
    if (tmp == "")
        num = 1;
    else if (tmp != "")
        num = stoi(tmp);
    if (sign == '-')
        num *= (-1);
    rez.key = power; 
    rez.pData = num;
    InsertInSort(rez);
}
TPolynom::TPolynom(const TPolynom& tmp)
{
    pol = new TList<unsigned int, double>(*tmp.pol);
}
TPolynom::~TPolynom()
{
    //pol->Reset();//delete pol
    //while (!pol->IsEnded())
    //{
    //    pol->Next();
    //    delete pol->pPrev;
    //}
    //delete pol->pCurr;
    //pol->pFirst = NULL;
    //pol->pCurr = NULL;
    //pol->pPrev = NULL;
    //pol->pNext = NULL;
    delete pol;
}

TPolynom TPolynom::operator+(const TPolynom& tm)
{
    TPolynom tmp(tm);
    tmp.pol->Reset();
    TPolynom rez(*this);
    rez.pol->Reset();
    while (tmp.pol->pCurr != NULL)
    {
        rez = rez + *tmp.pol->pCurr;
        tmp.pol->Next();
    }
    return rez;
}
TPolynom TPolynom::operator-(const TPolynom& tm)
{
    TPolynom rez = (*this) + (-tm);
    return rez;
}
TPolynom TPolynom::operator*(const TPolynom& tm)
{
    TPolynom tmp(tm);
    TPolynom tmp1(*this);
    tmp1.pol->Reset();
    tmp.pol->Reset();
    TPolynom rez;
    while (!tmp1.pol->IsEnded())
    {
        rez += tmp * *tmp1.pol->pCurr;
        tmp1.pol->Next();
    }
    return rez;
}
TPolynom TPolynom::operator+(const TMonom& tmp)
{
    TPolynom rez(*this);
    rez.pol->Reset(); 
    if (rez.pol->pFirst == NULL)//в операторе умножения создается пустой 
    {
        rez.pol->Back(tmp);
        return rez;
    }
    while ((rez.pol->pCurr != NULL) && (rez.pol->pCurr->key < tmp.key))
        rez.pol->Next();
    if (rez.pol->pCurr == NULL)
    {
        rez.pol->Back(tmp);
        return rez;
    }
    if (rez.pol->pCurr->key == tmp.key)
    {
        if (rez.pol->pCurr->pData + tmp.pData == 0)
        {
            rez.pol->Remove(rez.pol->pCurr->key);
        }
        else
        {
            *rez.pol->pCurr += tmp;
        }
    }
    else if (rez.pol->pCurr->key > tmp.key)
    {
        rez.pol->InsertBefore(tmp, rez.pol->pCurr->key);
    }
    return rez;
}
TPolynom TPolynom::operator-(const TMonom& tmp)
{
    TPolynom rez = *this + (-tmp);
    return rez;
}
TPolynom TPolynom::operator*(const TMonom& tmp)
{
    TPolynom rez;
    if (tmp.pData == 0)
        return rez;
    rez = *this;
    rez.pol->Reset();
    while (rez.pol->pCurr != NULL)
    {
        *rez.pol->pCurr *= tmp;
        rez.pol->Next();
    }
    return rez;
}
TPolynom TPolynom::operator*(double c)
{
    
    TPolynom rez;
    if (c == 0)
        return rez;
    rez = *this;
    rez.pol->Reset();
    while (!rez.pol->IsEnded())
    {
        *rez.pol->pCurr *= c;
        rez.pol->Next();
    }
    return rez;
}

TPolynom& TPolynom::operator=(const TPolynom& tm)
{
    if (*this == tm)
        return *this;
    delete pol;
    pol = new TList<unsigned int, double>(*tm.pol);
    return *this;
    //TPolynom tmp(tm);
    //tmp.pol->Reset();
    //pol->Reset();
    //
    ////delete[] pol;
    //while (!pol->IsEnded())
    //{
    //    pol->Next();
    //    delete pol->pPrev;
    //}
    //delete pol->pCurr;
    //pol->pFirst = NULL;
    //pol->pCurr = NULL;
    //pol->pPrev = NULL;
    //pol->pNext = NULL;
    //////delete
    //tmp.pol->Reset();
    //while (!tmp.pol->IsEnded())
    //{
    //    pol->Back(*tmp.pol->pCurr);
    //    //InsertSort(*tmp.pol->pCurr);
    //    tmp.pol->Next();
    //} 
    //DeleteNull();
    //return *this;
}
TPolynom& TPolynom::operator+=(const TPolynom& tm)
{
    TPolynom tmp = (*this) + tm;
    *this = tmp;
    return *this;
}
TPolynom& TPolynom::operator-=(const TPolynom& tm)
{
    TPolynom tmp = (*this) - tm;
    *this = tmp;
    return *this;
}
TPolynom& TPolynom::operator*=(const TPolynom& tm)
{
    TPolynom tmp = (*this) * tm;
    *this = tmp;
    return *this;
}
TPolynom& TPolynom::operator+=(const TMonom& tm)
{
    TPolynom tmp = (*this) * tm;
    *this = tmp;
    return *this;
}
TPolynom& TPolynom::operator-=(const TMonom& tm)
{
    TPolynom tmp = (*this) - tm;
    *this = tmp;
    return *this;
}
TPolynom& TPolynom::operator*=(const TMonom& tm)
{
    TPolynom tmp = (*this) * tm;
    *this = tmp;
    return *this;
}
TPolynom& TPolynom::operator*=(double c)
{
    TPolynom tmp = (*this) * c;
    *this = tmp;
    return *this;
}
TPolynom TPolynom::operator-() const
{
    TPolynom rez(*this);
    rez *= (-1);
    return rez;
}
bool TPolynom::operator==(const TPolynom& tmp)const
{
    TPolynom a(*this);
    TPolynom b(tmp);
    while ((!a.pol->IsEnded()) || (!b.pol->IsEnded()))
    {
        if (a.pol->pCurr != b.pol->pCurr)
            return false;
        a.pol->Next();
        b.pol->Next();
    }
    return true;
}

//double TPolynom::StToDouble(string a)//удалить и использовать встроенные функции
//{
//    double res = 0;
//    for (int i = 0; i < a.length(); i++)
//    {
//        switch (a[i])
//        {
//        case '0':
//            res += pow(10, (a.length() - i - 1)) * 0;
//            break;
//        case '1':
//            res += pow(10, (a.length() - i - 1)) * 1;
//            break;
//        case '2':
//            res += pow(10, (a.length() - i - 1)) * 2;
//            break;
//        case '3':
//            res += pow(10, (a.length() - i - 1)) * 3;
//            break;
//        case '4':
//            res += pow(10, (a.length() - i - 1 )) * 4;
//            break;
//        case '5':
//            res += pow(10, (a.length() - i - 1)) * 5;
//            break;
//        case '6':
//            res += pow(10, (a.length() - i - 1)) * 6;
//            break;
//        case '7':
//            res += pow(10, (a.length() - i - 1)) * 7;
//            break;
//        case '8':
//            res += pow(10, (a.length() - i - 1)) * 8;
//            break;
//        case '9':
//            res += pow(10, (a.length() - i - 1)) * 9;
//            break;
//        default:
//            break;
//        }
//    }
//    return res;
//}
bool TPolynom::IsDouble(string a)//нужна для проверки лимита степени(чтобы в степени каждого был только 1 символ)
{
    for (int i = 0; i < a.length(); i++)
    {
        if ((a[i] != '0') && (a[i] != '1') && (a[i] != '2') && (a[i] != '3') && (a[i] != '4') &&
            (a[i] != '5') && (a[i] != '6') && (a[i] != '7') && (a[i] != '8') && (a[i] != '9') && (a[i] != ' '))
            return false;
    }
    return true;
}
//TNode<int, double>& TPolynom::operator[](int n)
//{
//    TNode<int, double>* rez;
//    rez = pol->pFirst;
//    for (int i = 0; ((rez != NULL) && (i < n)); i++)
//        rez = rez->pNext;
//    return *rez;
//}
//
//const TNode<int, double>& TPolynom::operator[](int n) const
//{
//    TNode<int, double>* rez;
//    rez = pol->pFirst;
//    for (int i = 0; ((rez != NULL) && (i < n)); i++)
//        rez = rez->pNext;
//    return *rez;
//}
void TPolynom::InsertInSort(TMonom node)
{
    if ((node.key == 0) && (node.pData == 0))
        return;
    if (node.pData == 0)
        return;
    if (pol->pFirst == NULL)//если это первая вставка
    {
        pol->Back(node);
        return;
    }
    pol->Reset(); 
    while ((pol->pCurr->key < node.key) && (pol->pCurr->pNext != NULL))
    {
        pol->Next(); 
    }
    if (pol->pCurr->key == node.key)//если такой ключ был
    {
        pol->pCurr->pData = pol->pCurr->pData + node.pData;
        return;
    }
    else if (pol->pCurr->key > node.key)//такого ключа не было и он не наибольший
    {
        pol->InsertBefore(node, pol->pCurr->key);
        return;
    }
    pol->Back(node);//такого ключа не было и он наибольший
}
//void TPolynom::DeleteNull()//удалить и отлавливать в циклах
//{
//    pol->Reset();
//    while (!pol->IsEnded())
//    {
//        if (pol->pCurr->pData == 0)
//        {
//            pol->Remove(*pol->pCurr);
//        }
//        pol->Next();
//    }
//    pol->Reset();
//}
void TPolynom::CheckLim(const TList<unsigned int, double>* tm)const
{
    TList<unsigned int, double> tmp(*tm);
    tmp.Reset();
    while (!tmp.IsEnded())
    {
        if (tmp.pCurr->key > 999)
        {
            throw "!limit power";
        }
        tmp.Next();
    }
}