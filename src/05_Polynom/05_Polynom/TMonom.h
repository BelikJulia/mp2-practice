#pragma once
#include "List.h"
#include <iostream>

using namespace std;

template <>
class TNode<unsigned int, double>
{
public:
    unsigned int key;
    double pData;
    TNode* pNext;

    TNode();
    TNode(const TNode<unsigned int, double>&);
    TNode(unsigned int, double, TNode<unsigned int, double>*  next = 0);
    ~TNode();

    TNode& operator=(const TNode<unsigned int, double>&);
    bool operator==(const TNode<unsigned int, double>&)const;
    TNode operator+(const TNode<unsigned int, double>&);
    TNode operator-(const TNode<unsigned int, double>&);
    TNode operator*(const TNode<unsigned int, double>&);
    TNode operator*(double);
    TNode& operator+=(const TNode<unsigned int, double>&);
    TNode& operator-=(const TNode<unsigned int, double>&);
    TNode& operator*=(const TNode<unsigned int, double>&);
    TNode& operator*=(double);
    TNode operator-() const;

    friend ostream& operator<<(ostream& out, TNode<unsigned int, double>& node)
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


