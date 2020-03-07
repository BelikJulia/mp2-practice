#include "TPolynom.h"
#include <iostream>
#include <string>

using namespace std;

TNode<unsigned int, double>::TNode()
{
    key = 0;
    pData = 0;
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
    if (((tmp.key / 100 + key / 100) > 9) || ((tmp.key / 10 + key / 10) > 90) || ((tmp.key % 10 + key % 10) > 9))
        throw "!limit power";
    key += tmp.key;
    pData *= tmp.pData;
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
TPolynom::TPolynom(const TList<TNode<unsigned int, double> >* tm)
{
    TList<TNode<unsigned int, double> > tmp(*tm);
    tmp.Reset();
    while (!tmp.IsEnded())
    {
        if (tmp.pCurr->key > 999)
        {
            throw "!limit power";
        }
        tmp.Next();
    }
    //pol = new TList<TNode<int, double> >(*tmp);
    tmp.Reset();
    while (!tmp.IsEnded())
        InsertSort(*tmp.pCurr);
    DeleteNull();
}
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
                else
                    num = StToDouble(tmp);
                if (sign == '-')
                    num *= (-1);
                //TNode<unsigned int, double> rez(power, num);
                rez.key = power;
                rez.pData = num;
                InsertSort(rez);
                power = 0;
                num = 0;
                tmp = "";
                sign = '+';
                break;
            case '-':
               if ((tmp == "") && (power != 0))
                    num = 1;
                else
                    num = StToDouble(tmp);
                if (sign == '-')
                    num *= (-1);
                //TNode<unsigned int, double> rez(power, num);
                rez.key = power;
                rez.pData = num;
                InsertSort(rez);
                power = 0;
                num = 0;
                tmp = "";
                sign = '-';
                break;
            case '*':
                break;
            case '^':
                //do
                    i++;
                //while (st[i] == ' ');
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
                powerst = st[i + 1];
                if (IsDouble(powerst))
                    throw "limit power";
                else
                    powerst = "";
                /*do
                    i++;
                while (st[i] == ' ');
                powerst += st[i];
                if (IsDouble(powerst))
                    throw "limit power";
                else
                    i--;
                powerst = "";*/
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
    else
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
    pol = new TList<TNode<unsigned int, double> >();
    while (!tmp.pol->IsEnded())
    {
        pol->Back(*tmp.pol->pCurr);
        //InsertSort(*tmp.pol->pCurr);
        tmp.pol->Next();
    }
    DeleteNull();
}
TPolynom::~TPolynom()
{
    pol->Reset();
    while (!pol->IsEnded())
    {
        pol->Next();
        delete pol->pPrev;
    }
    delete pol->pCurr;
    pol->pFirst = NULL;
    pol->pCurr = NULL;
    pol->pPrev = NULL;
    pol->pNext = NULL;
    //delete[]pol;
}

TPolynom TPolynom::operator+(const TPolynom& tm)
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
    TPolynom tmp(tm); 
    pol->Reset();
    tmp.pol->Reset();
    TPolynom rez(*this);
    while (tmp.pol->pCurr != NULL)
    {
        rez = rez + *tmp.pol->pCurr;
        tmp.pol->Next();
    }
    rez.DeleteNull(); 
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext; 
    return rez;
}
TPolynom TPolynom::operator-(const TPolynom& tm)
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
    TPolynom tmp(tm);
    pol->Reset();
    tmp.pol->Reset();
    TPolynom rez(*this);
    while (tmp.pol->pCurr != NULL)
    {
        rez = rez - *tmp.pol->pCurr;
        tmp.pol->Next();
    }
    rez.DeleteNull();
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
    return rez;
}
TPolynom TPolynom::operator*(const TPolynom& tm)
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
    TPolynom tmp(tm);
    pol->Reset();
    tmp.pol->Reset();
    TPolynom rez(tmp);
    try
    {
        rez = tmp * *pol->pFirst;
        pol->Next(); 
        while (!pol->IsEnded())
        {
            rez += tmp * *pol->pCurr;
            pol->Next();
        }
    }
    catch (char* er)
    {
        throw er;
    }
    rez.DeleteNull(); 
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
    return rez;
}
TPolynom TPolynom::operator+(TNode<unsigned int, double> tmp)
{ 
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
    TPolynom rez(*this);
    rez.pol->Reset(); 
    while ((rez.pol->pCurr->key < tmp.key) && (rez.pol->pCurr/*->pNext*/ != NULL))
        rez.pol->Next();
    if (rez.pol->pCurr->key == tmp.key)
        *rez.pol->pCurr += tmp;
    else if (rez.pol->pCurr->key > tmp.key)
    {
        TNode<unsigned int, double> node(tmp);
        rez.pol->InsertBefore(*(rez.pol->pCurr), node);
    }
    else
    {
        TNode<unsigned int, double> node(tmp);
        rez.pol->Back(node);
    }
    rez.DeleteNull();
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
    return rez;
}
TPolynom TPolynom::operator-(TNode<unsigned int, double> tmp)
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
    TPolynom rez(*this);
    rez.pol->Reset();
    while ((rez.pol->pCurr->key < tmp.key) && (rez.pol->pCurr/*->pNext*/ != NULL))
        rez.pol->Next();
    if (rez.pol->pCurr->key == tmp.key)
        *rez.pol->pCurr -= tmp;
    else if (rez.pol->pCurr->key > tmp.key)
    {
        TNode<unsigned int, double> node(tmp);
        node *= (-1);
        rez.pol->InsertBefore(*(rez.pol->pCurr), node);
    }
    else
    {
        TNode<unsigned int, double> node(tmp);
        node *= (-1);
        rez.pol->Back(node);
    }
    rez.DeleteNull();
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
    return rez;
}
TPolynom TPolynom::operator*(TNode<unsigned int, double> tmp)
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
    TPolynom rez(*this);
    rez.pol->Reset(); 
    try
    {
        while (rez.pol->pCurr != NULL)
        {
            *rez.pol->pCurr *= tmp;
            rez.pol->Next();
        }
    }
    catch (char* er)
    {
        throw er;
    }
    rez.DeleteNull();
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
    return rez;
}
TPolynom TPolynom::operator*(double c)
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
    TPolynom rez(*this);
    rez.pol->Reset();
    while (!rez.pol->IsEnded())
    {
        *rez.pol->pCurr *= c;
        rez.pol->Next();
    }
    rez.DeleteNull();
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
    return rez;
}

TPolynom& TPolynom::operator=(const TPolynom& tm)
{
    TPolynom tmp(tm);
    tmp.pol->Reset();
    pol->Reset();
    if (this == &tmp)
        return *this;
    //delete[] pol;
    while (!pol->IsEnded())
    {
        pol->Next();
        delete pol->pPrev;
    }
    delete pol->pCurr;
    pol->pFirst = NULL;
    pol->pCurr = NULL;
    pol->pPrev = NULL;
    pol->pNext = NULL;
    ////delete
    tmp.pol->Reset();
    while (!tmp.pol->IsEnded())
    {
        pol->Back(*tmp.pol->pCurr);
        //InsertSort(*tmp.pol->pCurr);
        tmp.pol->Next();
    } 
    DeleteNull();
    return *this;
}
TPolynom& TPolynom::operator+=(const TPolynom& tm)
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
    TPolynom tmp(tm);
    tmp.pol->Reset();
    while (!tmp.pol->IsEnded())
    {
        *this += *tmp.pol->pCurr;
        tmp.pol->Next();
    }
    DeleteNull();
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
    return *this;
}
TPolynom& TPolynom::operator-=(const TPolynom& tm)
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
    TPolynom tmp(tm);
    tmp.pol->Reset();
    while (!tmp.pol->IsEnded())
    {
        *this -= *tmp.pol->pCurr;
        tmp.pol->Next();
    }
    DeleteNull();
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
    return *this;
}
TPolynom& TPolynom::operator*=(const TPolynom& tm)
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
    TPolynom tmp(tm);
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
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
    return *this;
}
TPolynom& TPolynom::operator+=(TNode<unsigned int, double> tmp)
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
    pol->Reset();
    while ((pol->pCurr != NULL) && (pol->pCurr->key < tmp.key))
        pol->Next();
    if (pol->pCurr != NULL)
    {
        if (pol->pCurr->key == tmp.key)
            *pol->pCurr += tmp;
        if (pol->pCurr->key > tmp.key)
        {
            TNode<unsigned int, double> node(tmp);
            pol->InsertBefore(*(pol->pCurr), node);
        }
    }
    else
        pol->Back(tmp);
    DeleteNull();
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
    return *this;
}
TPolynom& TPolynom::operator-=(TNode<unsigned int, double> tmp)
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
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
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
    return *this;
}
TPolynom& TPolynom::operator*=(TNode<unsigned int, double> tmp)
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
    pol->Reset();
    while (!pol->IsEnded())
    {
        *pol->pCurr *= tmp;
        pol->Next();
    }
    DeleteNull();
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
    return *this;
}
TPolynom& TPolynom::operator*=(double c)
{
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
    pol->Reset();
    while (!pol->IsEnded())
    {
        *pol->pCurr *= c;
        pol->Next();
    }
    DeleteNull();
    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
    return *this;
}
TPolynom TPolynom::operator-() const
{
    TPolynom rez(*this);
    TNode<unsigned, double>* node = rez.pol->pFirst;
    while (node != NULL)
    {
        node->pData *= -1;
        node = node->pNext;
    }
    return rez;
}

double TPolynom::StToDouble(string a)
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
            res += pow(10, (a.length() - i - 1 )) * 4;
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
bool TPolynom::IsDouble(string a)
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
void TPolynom::InsertSort(TNode<unsigned int, double> node)
{
    if ((node.key == 0) && (node.pData == 0))
        return;
    TNode<unsigned int, double>* pprev = pol->pPrev;
    TNode<unsigned int, double>* pcurr = pol->pCurr;
    TNode<unsigned int, double>* pnext = pol->pNext;
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
        pol->pCurr->pData += node.pData;
        return;
    }
    else if (pol->pCurr->key > node.key)//такого ключа не было и он не наибольший
    {
        pol->InsertBefore(*(pol->pCurr), node);
        return;
    }
    pol->Back(node);//такого ключа не было и он наибольший
        

    pol->pPrev = pprev;
    pol->pCurr = pcurr;
    pol->pNext = pnext;
}
void TPolynom::DeleteNull()
{
    pol->Reset();
    while (!pol->IsEnded())
    {
        if (pol->pCurr->pData == 0)
        {
            pol->Remove(*pol->pCurr);
        }
        pol->Next();
    }
    pol->Reset();
}