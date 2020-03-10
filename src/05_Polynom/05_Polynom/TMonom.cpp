#include "TMonom.h"
#include <iostream>
#include <string>

using namespace std;

typedef TNode<unsigned int, double> TMonom;

TNode<unsigned int, double>::TNode()
{
    key = 0;
    pData = 0;
    pNext = NULL;
}
TNode<unsigned int, double>::TNode(const TMonom& tmp)
{
    key = tmp.key;
    pData = tmp.pData;
    pNext = NULL;
}
TNode<unsigned int, double>::TNode(unsigned int _conv, double _coeff, TNode<unsigned int, double> * next)
{
    key = _conv;
    pData = _coeff;
    pNext = next;
}
TNode<unsigned int, double>::~TNode()
{}

TMonom& TNode<unsigned int, double>::operator=(const TNode<unsigned int, double> & tmp)
{
    if (*this == tmp)
        return *this;
    key = tmp.key;
    pData = tmp.pData;
    pNext = NULL;
}
bool TNode<unsigned int, double>::operator==(const TNode<unsigned int, double> & tmp)const
{
    if ((tmp.key != key) || (tmp.pData != pData))
        return false;
    return true;
}
TMonom TNode<unsigned int, double>::operator+(const TNode<unsigned int, double> & tmp)
{
    if (key != tmp.key)
        throw "!diff conv";
    TMonom rez(tmp);
    rez.pData += pData;
    return rez;
}
TMonom TNode<unsigned int, double>::operator-(const TNode<unsigned int, double> & tmp)
{
    if (key != tmp.key)
        throw "!diff conv";
    TMonom rez(*this);
    rez.pData -= tmp.pData;
    return rez;
}
TMonom TNode<unsigned int, double>::operator*(const TNode<unsigned int, double> & tmp)
{
    if (((tmp.key / 100) + (key / 100) > 9) || (((tmp.key / 10) % 10) + ((key / 10) % 10) > 9) ||
        ((tmp.key % 10) + (key % 10) > 9))
        throw "!limit power";
    TMonom rez;
    rez.pData = pData * tmp.pData;
    rez.key = key + tmp.key;
    return rez;
}
TMonom TNode<unsigned int, double>::operator*(double c)
{
    TMonom rez(*this);
    rez.pData *= c;
    return rez;
}

TMonom& TNode<unsigned int, double>::operator+=(const TNode<unsigned int, double> & tmp)
{
    if (key != tmp.key)
        throw "!diff conv";
    pData += tmp.pData;
    return *this;
}
TMonom& TNode<unsigned int, double>::operator-=(const TNode<unsigned int, double> & tmp)
{
    if (key != tmp.key)
        throw "!diff conv";
    pData -= tmp.pData;
    return *this;
}
TMonom& TNode<unsigned int, double>::operator*=(const TNode<unsigned int, double> & tmp)
{
    if (((tmp.key / 100 + key / 100) > 9) || ((tmp.key / 10 + key / 10) > 90)
        || ((tmp.key % 10 + key % 10) > 9))
        throw "!limit power";
    key += tmp.key;
    pData *= tmp.pData;
    return *this;
}
TMonom& TNode<unsigned int, double>::operator*=(double c)
{
    pData *= c;
    return *this;
}
TMonom TNode<unsigned int, double> ::operator-() const
{
    TMonom rez(*this);
    rez *= (-1);
    return rez;
}