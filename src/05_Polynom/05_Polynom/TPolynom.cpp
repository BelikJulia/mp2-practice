#include "TPolynom.h"
#include <iostream>
#include <string>

using namespace std;

TNode<unsigned int, double>::TNode()
{
    pNext = NULL;
}
TNode<unsigned int, double>::TNode(const TNode& tmp)
{
    key = tmp.key;
    pData = tmp.pData;
    pNext = NULL;
}
TNode<unsigned int, double>::TNode(unsigned int _conv, double _coeff, TNode* next)
{
    key = _conv;
    pData = _coeff;
    pNext = next;
}
TNode<unsigned int, double>::~TNode()
{}

TNode<unsigned int, double>& TNode<unsigned int, double>::operator=(const TNode& tmp)
{
    if (this == &tmp)
        return *this;
    key = tmp.key;
    pData = tmp.pData;
    pNext = NULL;
}
TNode<unsigned int, double> TNode<unsigned int, double>::operator+(const TNode& tmp)
{
    if (key != tmp.key)
        throw "!diff conv";
    TNode<unsigned int, double> rez(tmp);
    rez.pData += pData;
    return rez;
}
TNode<unsigned int, double> TNode<unsigned int, double>::operator-(const TNode& tmp)
{
    if (key != tmp.key)
        throw "!diff conv";
    TNode<unsigned int, double> rez(*this);
    rez.pData -= tmp.pData;
    return rez;
}
TNode<unsigned int, double> TNode<unsigned int, double>::operator*(const TNode& tmp)
{
    if (((tmp.key / 100) + (key / 100) > 9) || (((tmp.key / 10) % 10) + ((key / 10) % 10) > 9) || ((tmp.key % 10) + (key % 10) > 9))
        throw "!limit power";
    TNode<unsigned int, double> rez;
    rez.pData = pData * tmp.pData;
    rez.key = key + tmp.key;
    return rez;
}
TNode<unsigned int, double> TNode<unsigned int, double>::operator*(double c)
{
    TNode<unsigned int, double> rez(*this);
    rez.pData *= c;
    return rez;
}

TNode<unsigned int, double>& TNode<unsigned int, double>::operator+=(const TNode& tmp)
{
    if (key != tmp.key)
        throw "!diff conv";
    pData += tmp.pData;
    return *this;
}
TNode<unsigned int, double>& TNode<unsigned int, double>::operator-=(const TNode& tmp)
{
    if (key != tmp.key)
        throw "!diff conv";
    pData -= tmp.pData;
    return *this;
}
TNode<unsigned int, double>& TNode<unsigned int, double>::operator*=(const TNode& tmp)
{
    if (((tmp.key / 100) + (key / 100) > 9) || (((tmp.key / 10) % 10) + ((key / 10) % 10) > 9) || ((tmp.key % 10) + (key % 10) > 9))
        throw "!limit power";
    pData *= tmp.pData;
    key += tmp.key;
    return *this;
}
TNode<unsigned int, double>& TNode<unsigned int, double>::operator*=(double c)
{
    pData *= c;
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////

TPolynom::TPolynom()
{
    pol = new TList<TNode<unsigned int, double> >();
}
//TPolynom::TPolynom(const TList<TNode<unsigned int, double> >* tmp)
//{
//    tmp->Reset();
//    while (!tmp->IsEnded())
//    {
//        if (tmp->pCurr->key > 999)
//        {
//            throw "!limit power";
//        }
//        tmp->Next();
//    }
//    //pol = new TList<TNode<int, double> >(*tmp);
//    tmp->Reset();
//    while (!tmp->IsEnded())
//        InsertSort(*tmp->pCurr);
//    DeleteNull();
//}
TPolynom::TPolynom(const string& st)
{
    if (st == "")
        throw "!empty line";
    pol = new TList<TNode<unsigned int, double> >();
    string tmp = "";
    string powerst = "";
    char sign = '+';
    char nowis = ' ';
    unsigned int power = 0;
    double num = 0;
    int i = 0;
    TNode<unsigned int, double> rez;
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
                num = StToDouble(tmp);
                if (sign == '-')
                    num *= (-1);
                //TNode<unsigned int, double> rez(power, num);
                rez.key = power;
                rez.pData = num;
                InsertSort(rez);
                sign = '+';
                break;
            case '-':
                num = StToDouble(tmp);
                if (sign == '-')
                    num *= (-1);
                //TNode<unsigned int, double> rez(power, num);
                rez.key = power;
                rez.pData = num;
                InsertSort(rez);
                sign = '-';
                break;
            case '*':
                break;
            case '^':
                do
                    i++;
                while (st[i] == ' ');
                powerst += st[i];
                switch (nowis)
                {
                case 'x':
                    power += (StToDouble(powerst) - 1) * 100;
                    break;
                case 'y':
                    power += (StToDouble(powerst) - 1) * 10;
                    break;
                case 'z':
                    power += StToDouble(powerst) - 1;
                    break;
                }
                powerst = "";
                do
                    i++;
                while (st[i] == ' ');
                powerst += st[i];
                if (IsDouble(powerst))
                    throw "limit power";
                else
                    i--;
                powerst = "";
                break;
            default:
                tmp += st[i];
                break;
            }
        }
        i++;
    }
    num = StToDouble(tmp);
    if (sign == '-')
        num *= (-1);
    rez.key = power;
    rez.pData = num;
    InsertSort(rez);
    DeleteNull();
}
TPolynom::TPolynom(const TPolynom& tmp)
{
    tmp.pol->Reset();
    while (!tmp.pol->IsEnded())
    {
        if (tmp.pol->pCurr->key > 999)
            throw "limit power";
        tmp.pol->Next();
    }
    tmp.pol->Reset();
    while (!tmp.pol->IsEnded())
    {
        InsertSort(*tmp.pol->pCurr);
        tmp.pol->Next();
    }
    DeleteNull();
}
TPolynom::~TPolynom()
{
    delete[]pol;
}

TPolynom TPolynom::operator+(const TPolynom& tmp)
{
    pol->Reset();
    tmp.pol->Reset();
    TPolynom rez(*this);
    while (!tmp.pol->IsEnded())
    {
        rez = rez - *tmp.pol->pCurr;
        pol->Next();
    }
    rez.DeleteNull();
    return rez;
}
TPolynom TPolynom::operator-(const TPolynom& tmp)
{
    pol->Reset();
    tmp.pol->Reset();
    TPolynom rez(tmp);
    while (!pol->IsEnded())
    {
        rez = rez + *pol->pCurr;
        pol->Next();
    }
    rez.DeleteNull();
    return rez;
}
TPolynom TPolynom::operator*(const TPolynom& tmp)
{
    pol->Reset();
    tmp.pol->Reset();
    TPolynom rez(tmp);
    while (!pol->IsEnded())
    {
        rez += *this * *pol->pCurr;
        pol->Next();
    }
    rez.DeleteNull();
    return rez;
}
TPolynom TPolynom::operator+(TNode<unsigned int, double> tmp)
{
    TPolynom rez(*this);
    rez.pol->Reset();
    while ((rez.pol->pCurr->key < tmp.key) && (!rez.pol->IsEnded()))
        rez.pol->Next();
    if (rez.pol->pCurr->key == tmp.key)
        *rez.pol->pCurr += tmp;
    if (rez.pol->pCurr->key > tmp.key)
    {
        TNode<unsigned int, double> node(tmp);
        rez.pol->InsertBefore(*(rez.pol->pCurr), node);
    }
    rez.DeleteNull();
    return rez;
}
TPolynom TPolynom::operator-(TNode<unsigned int, double> tmp)
{
    TPolynom rez(*this);
    rez.pol->Reset();
    while ((rez.pol->pCurr->key < tmp.key) && (!rez.pol->IsEnded()))
        rez.pol->Next();
    if (rez.pol->pCurr->key == tmp.key)
        *rez.pol->pCurr -= tmp;
    if (rez.pol->pCurr->key > tmp.key)
    {
        TNode<unsigned int, double> node(tmp);
        node = node * (-1);
        rez.pol->InsertBefore(*(rez.pol->pCurr), node);
    }
    rez.DeleteNull();
    return rez;
}
TPolynom TPolynom::operator*(TNode<unsigned int, double> tmp)
{
    TPolynom rez(*this);
    rez.pol->Reset();
    while (!rez.pol->IsEnded())
        *rez.pol->pCurr *= tmp;
    rez.DeleteNull();
    return rez;
}
TPolynom TPolynom::operator*(double c)
{
    TPolynom rez(*this);
    rez.pol->Reset();
    while (!rez.pol->IsEnded())
        *rez.pol->pCurr *= c;
    rez.DeleteNull();
    return rez;
}

TPolynom& TPolynom::operator=(const TPolynom& tmp)
{
    tmp.pol->Reset();
    pol->Reset();
    if (this == &tmp)
        return *this;
    delete[] pol;
    while (!tmp.pol->IsEnded())
    {
        if (tmp.pol->pCurr->key > 999)
            throw "limit power";
        tmp.pol->Next();
    }
    tmp.pol->Reset();
    while (!tmp.pol->IsEnded())
    {
        InsertSort(*tmp.pol->pCurr);
        tmp.pol->Next();
    }
    DeleteNull();
    return *this;
}
TPolynom& TPolynom::operator+=(const TPolynom& tmp)
{
    tmp.pol->Reset();
    while (!tmp.pol->IsEnded())
    {
        *this += *tmp.pol->pCurr;
        pol->Next();
    }
    DeleteNull();
    return *this;
}
TPolynom& TPolynom::operator-=(const TPolynom& tmp)
{
    tmp.pol->Reset();
    while (!tmp.pol->IsEnded())
    {
        *this -= *tmp.pol->pCurr;
        pol->Next();
    }
    DeleteNull();
    return *this;
}
TPolynom& TPolynom::operator*=(const TPolynom& tmp)
{
    tmp.pol->Reset();
    TPolynom rez(*this);
    *this *= *tmp.pol->pCurr;
    tmp.pol->Next();
    while (!tmp.pol->IsEnded())
    {
        *this += rez * *tmp.pol->pCurr;
        tmp.pol->Next();
    }
    DeleteNull();
    return *this;
}
TPolynom& TPolynom::operator+=(TNode<unsigned int, double> tmp)
{
    pol->Reset();
    while ((pol->pCurr->key < tmp.key) && (!pol->IsEnded()))
        pol->Next();
    if (pol->pCurr->key == tmp.key)
        *pol->pCurr += tmp;
    if (pol->pCurr->key > tmp.key)
    {
        TNode<unsigned int, double> node(tmp);
        pol->InsertBefore(*(pol->pCurr), node);
    }
    DeleteNull();
    return *this;
}
TPolynom& TPolynom::operator-=(TNode<unsigned int, double> tmp)
{
    pol->Reset();
    while ((pol->pCurr->key < tmp.key) && (!pol->IsEnded()))
        pol->Next();
    if (pol->pCurr->key == tmp.key)
        *pol->pCurr -= tmp;
    if (pol->pCurr->key > tmp.key)
    {
        TNode<unsigned int, double> node(tmp);
        node = node * (-1);
        pol->InsertBefore(*(pol->pCurr), node);
    }
    DeleteNull();
    return *this;
}
TPolynom& TPolynom::operator*=(TNode<unsigned int, double> tmp)
{
    pol->Reset();
    while (!pol->IsEnded())
        *pol->pCurr *= tmp;
    DeleteNull();
    return *this;
}
TPolynom& TPolynom::operator*=(double c)
{
    pol->Reset();
    while (!pol->IsEnded())
        *pol->pCurr *= c;
    DeleteNull();
    return *this;
}

double TPolynom::StToDouble(string a)
{
    double res = 0;
    for (int i = 0; i < a.length(); i++)
    {
        switch (a[i])
        {
        case '0':
            res += pow(10, (a.length() - i)) * 0;
            break;
        case '1':
            res += pow(10, (a.length() - i)) * 1;
            break;
        case '2':
            res += pow(10, (a.length() - i)) * 2;
            break;
        case '3':
            res += pow(10, (a.length() - i)) * 3;
            break;
        case '4':
            res += pow(10, (a.length() - i)) * 4;
            break;
        case '5':
            res += pow(10, (a.length() - i)) * 5;
            break;
        case '6':
            res += pow(10, (a.length() - i)) * 6;
            break;
        case '7':
            res += pow(10, (a.length() - i)) * 7;
            break;
        case '8':
            res += pow(10, (a.length() - i)) * 8;
            break;
        case '9':
            res += pow(10, (a.length() - i)) * 9;
            break;
        default:
            break;
        }
    }
    return res;
}
bool TPolynom::IsDouble(string a)
{
    for (int i = 0; i < a.length(); i++)
        if ((a[i] != '0') || (a[i] != '1') || (a[i] != '2') || (a[i] != '3') || (a[i] != '4') ||
            (a[i] != '5') || (a[i] != '6') || (a[i] != '7') || (a[i] != '8') || (a[i] != '9') || (a[i] != ' '))
            return false;
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
void TPolynom::InsertSort(TNode<unsigned int, double> node)
{
    //TNode<unsigned int, double>* pprev = pol->pPrev;
    //TNode<unsigned int, double>* pcurr = pol->pCurr;
    //TNode<unsigned int, double>* pnext = pol->pNext;

    pol->Reset();
    if (pol->IsEnded())//если это первая вставка
        pol->Back(node);
    while ((pol->pCurr->key < node.key) && (!pol->IsEnded()))
        pol->Next();
    if (pol->pCurr->key == node.key)//если такй ключ был
        pol->pCurr->pData += node.pData;
    else if ((pol->pCurr->key > node.key) && (!pol->IsEnded()))//такого ключа не было и он не наибольший
        pol->InsertBefore(*(pol->pCurr), node);
    else if (pol->IsEnded())//самый большой ключ
        pol->Back(node);

    //pol->pPrev = pprev;
    //pol->pCurr = pcurr;
    //pol->pNext = pnext;
}
void TPolynom::DeleteNull()
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;

    pol->Reset();
    while (!pol->IsEnded())
    {
        if (pol->pCurr->pData == 0)
            pol->Remove(*pol->pCurr);
        pol->Next();
    }

    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
}