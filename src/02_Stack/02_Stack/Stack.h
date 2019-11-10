#pragma once
#include <iostream>

using namespace std;

template <class VT>
class TStack
{
private:
    VT* elems;
    int size;
    int top;
public:
    TStack(int _size = 10);
    TStack(const TStack<VT>& tmp);
    ~TStack();
    void Push(VT a);
    VT Pop();
    VT NPop();
    TStack& operator=(const TStack& tmp);
    bool IsFull();
    bool IsEmpty();
    int GetSize();

    friend istream& operator>>(istream& in, TStack<VT>& s)
    {
        top = size;
        for (int i = 0; i < s.size; i++)
            in >> s.elems[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TStack<VT>& s)
    {
        for (int i = 0; i < s.top; i++)
            out << s.elems[i];
        return out;
    }
};

template <class VT>
TStack<VT>::TStack(int _size)
{
    size = _size;
    top = 0;
    elems = new VT[size];
}

template <class VT>
TStack<VT>::TStack(const TStack<VT>& tmp)
{
    size = tmp.size;
    top = tmp.top;
    elems = new VT[size];
    for (int i = 0; i < size; i++)
    {
        elems[i] = tmp.elems[i];
    }
}

template <class VT>
TStack<VT>::~TStack()
{
    size = 0;
    top = 0;
    delete[] elems;
}

template <class VT>
void TStack<VT>::Push(VT a)
{
    if (this->IsFull())
        throw "Is Full";
    elems[top++] = a;
}

template <class VT>
VT TStack<VT>::Pop()
{
    if (this->IsEmpty())
        throw "Is Empty";
    return elems[--top];
}

template <class VT>
VT TStack<VT>::NPop()
{
    if (this->IsEmpty())
        throw "Is Empty";
    VT res = elems[0];
    for (int i = 0; i < top - 1; i++)
        elems[i] = elems[i + 1];
    return res;
}

template <class VT>
bool TStack<VT>::IsFull()
{
    return (top == size);
}

template <class VT>
bool TStack<VT>::IsEmpty()
{
    return (top == 0);
}

template<class VT>
TStack<VT>& TStack<VT>::operator=(const TStack<VT>& tmp)
{
    /*if (*this == tmp)
        return *this;*/
    size = tmp.size;
    top = tmp.top;
    delete[] elems;
    elems = new VT[size];
    for (int i = 0; i < size; i++)
    {
        elems[i] = tmp.elems[i];
    }
    return *this;
}

template <class VT>
int TStack<VT>::GetSize()
{
    return size;
}