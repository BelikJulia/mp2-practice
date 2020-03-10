#pragma once
#include "List.h"
#include "TMonom.h"
#include <iostream>

using namespace std;

typedef TNode<unsigned int, double> TMonom;

class TPolynom
{
private:
    TList<unsigned int, double>* pol;
    void InsertInSort(TMonom node);
    bool IsDouble(string a);
    void CheckLim(const TList<unsigned int, double>*)const;
public:
    TPolynom();
    TPolynom(const TList<unsigned int, double>*);
    TPolynom(const string&);
    TPolynom(const TPolynom&);
    ~TPolynom();

    TPolynom operator+(const TPolynom&);
    TPolynom operator-(const TPolynom&);
    TPolynom operator*(const TPolynom&);
    TPolynom operator+(const TMonom&);
    TPolynom operator-(const TMonom&);
    TPolynom operator*(const TMonom&);
    TPolynom operator*(double);
    TPolynom& operator+=(const TPolynom&);
    TPolynom& operator-=(const TPolynom&);
    TPolynom& operator*=(const TPolynom&);
    TPolynom& operator+=(const TMonom&);
    TPolynom& operator-=(const TMonom&);
    TPolynom& operator*=(const TMonom&);
    TPolynom& operator*=(double);
    TPolynom& operator=(const TPolynom&);
    bool operator==(const TPolynom&)const;
    TPolynom operator-() const;

    friend ostream& operator<<(ostream& out, TPolynom& tmp)
    {
        TMonom* pprev = tmp.pol->pPrev;
        TMonom* pcurr = tmp.pol->pCurr;
        TMonom* pnext = tmp.pol->pNext;
        tmp.pol->Reset();
        while (!tmp.pol->IsEnded())
        {
            out << *(tmp.pol->pCurr);
            tmp.pol->Next();
        }
        tmp.pol->pPrev = pprev;
        tmp.pol->pCurr = pcurr;
        tmp.pol->pNext = pnext;
        return out;
    }
    /*friend istream& operator>>(istream& in, TPolynom& tmp)
    {
        string st;
        getline(in, st);
        tmp = TPolynom(st);
        return in;
    }*/
};