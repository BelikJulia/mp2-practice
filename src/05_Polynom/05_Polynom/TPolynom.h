#pragma once
#include "List.h"
#include <iostream>

using namespace std;

template <>
class /*TMonom::public*/ TNode<unsigned int, double>
{
    //private:
public:
    unsigned int key;
    double pData;
    TNode* pNext;
    //public:
    TNode();
    TNode(const TNode&);
    TNode(unsigned int, double, TNode*  next = 0);
    ~TNode();

    TNode& operator=(const TNode&);
    TNode operator+(const TNode&);
    TNode operator-(const TNode&);
    TNode operator*(const TNode&);
    TNode operator*(double);//перегрузка унарный минус
    TNode& operator+=(const TNode&);
    TNode& operator-=(const TNode&);
    TNode& operator*=(const TNode&);
    TNode& operator*=(double);

    friend ostream& operator<<(ostream& out, TNode& node)
    {
        if (node.pData > 0)
            out << "+";
        out << node.pData;
        if (node.key / 100 != 0)
            out << "x^" << node.key / 100;
        if ((node.key / 10) % 10 != 0)
            out << "y^" << (node.key / 10) % 10;
        if (node.key % 10 != 0)
            out << "z^" << node.key % 10;
        out << " ";
        return out;
    }
};

class TPolynom
{
protected:
    TList<TNode<unsigned int, double> >* pol;
    double StToDouble(string a);
    bool IsDouble(string a);
    void InsertSort(TNode<unsigned int, double> node);
    void DeleteNull();
    //TNode<int, double>& operator[](int n);
    //const TNode<int, double>& operator[](int n) const;
public:
    TPolynom();
    TPolynom(const TList<TNode<unsigned int, double> >*);
    TPolynom(const string&);
    TPolynom(const TPolynom&);
    ~TPolynom();

    TPolynom operator+(const TPolynom&);
    TPolynom operator-(const TPolynom&);
    TPolynom operator*(const TPolynom&);
    TPolynom operator+(TNode<unsigned int, double>);
    TPolynom operator-(TNode<unsigned int, double>);
    TPolynom operator*(TNode<unsigned int, double>);
    TPolynom operator*(double);
    TPolynom& operator+=(const TPolynom&);
    TPolynom& operator-=(const TPolynom&);
    TPolynom& operator*=(const TPolynom&);
    TPolynom& operator+=(TNode<unsigned int, double>);
    TPolynom& operator-=(TNode<unsigned int, double>);
    TPolynom& operator*=(TNode<unsigned int, double>);
    TPolynom& operator*=(double);
    TPolynom& operator=(const TPolynom&);
    TPolynom operator-() const;

    friend ostream& operator<<(ostream& out, TPolynom& tmp)
    {
        TNode<unsigned int, double>* pprev = tmp.pol->pPrev;
        TNode<unsigned int, double>* pcurr = tmp.pol->pCurr;
        TNode<unsigned int, double>* pnext = tmp.pol->pNext;
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
};