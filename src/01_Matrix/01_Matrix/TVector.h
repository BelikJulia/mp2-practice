#pragma once
#include <iostream>
#include <math.h>

using namespace std;

template<typename T>
class TVector
{
protected: 
//public:
    int size;
    T* arr;
    int startindex;
public:
    TVector();
    TVector(int _size, int _startindex);
    TVector(int _size);
    TVector(const TVector& tmp);
    ~TVector();

    TVector& operator=(const TVector& tmp);//const;
    T len() const;
    TVector operator+(const T a);
    TVector operator-(const T a);
    TVector operator*(const T a);
    TVector operator+(const TVector& tmp);
    TVector operator-(const TVector& tmp);
    T operator*(const TVector& tmp);
    bool operator==(const TVector& tmp)const;
    bool operator!=(const TVector& tmp)const;
    int GetSI()const;
    int GetSize()const;

    T& operator[] (int i);
    const T& operator[] (int i) const;

    friend istream& operator>>(istream& in, TVector<T>& v)
    {
        for (int i = 0; i < v.size; i++)
            in >> v.arr[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TVector<T>& v)
    {
        for (int i = 0; i < v.startindex; i++)
            out << "0 ";
        for (int i = 0; i < v.size; i++)
            out << v.arr[i] << " ";
        return out;
    }
};


template<typename T>
TVector<T>::TVector()
{
    //this->size = 0;
    //this->startindex = 0;
}

template<typename T>
TVector<T>::TVector(int _size, int _startindex)
{
    this->size = _size;
    this->startindex = _startindex;
    this->arr = new T[this->size];
}

template<typename T>
TVector<T>::TVector(int _size)
{
    this->size = _size;
    this->arr = new T[this->size];
}

template<typename T>
TVector<T>::TVector(const TVector<T>& tmp)
{
    this->size = tmp.size;
    this->startindex = tmp.startindex;
    this->arr = new T[this->size];
//    memcpy(tmp.arr, this->arr, sizeof(T) * this->size);
    for (int i = 0; i < this->size; i++)
        this->arr[i] = tmp.arr[i];
}

template<typename T>
TVector<T>::~TVector()
{
    this->size = 0;
//    delete this->arr;
}

template<typename T>
TVector<T>& TVector<T>::operator=(const TVector<T>& tmp)//const
{
    if (*this == tmp)
        return *this;
    if (this->size != tmp.size)
    {
        this->size = tmp.size;
//        delete this->arr;
        this->arr = new T[this->size];
    }
//    memcpy(tmp.arr, this->arr, sizeof(T) * this->size);
    this->startindex = tmp.startindex;
    for (int i = 0; i < this->size; i++)
        this->arr[i] = tmp.arr[i];
    return *this;
}

template<typename T>
T TVector<T>::len() const
{
    T rez = 0;
    for (int i = 0; i < this->size; i++)
        rez += this->arr[i] * this->arr[i];
    return sqrt(rez);
}

template<typename T>
TVector<T> TVector<T>::operator+(const T a)
{
    TVector<T> rez(this->size);
    for (int i = 0; i < this->size; i++)
        rez.arr[i] = this->arr[i] + a;
    return rez;
}

template<typename T>
TVector<T> TVector<T>::operator-(const T a)
{
    TVector<T> rez(this->size);
    for (int i = 0; i < this->size; i++)
        rez.arr[i] = this->arr[i] - a;
    return rez;
}

template<typename T>
TVector<T> TVector<T>::operator*(const T a)
{
    TVector<T> rez(this->size);
    for (int i = 0; i < this->size; i++)
        rez.arr[i] = this->arr[i] * a;
    return rez;
}

template<typename T>
TVector<T> TVector<T>::operator+(const TVector<T>& tmp)
{
    if (this->size != tmp.size)
        throw "!size";
    TVector<T> rez(this->size);
    for (int i = 0; i < this->size; i++)
        rez.arr[i] = this->arr[i] + tmp.arr[i];
    return rez;
}

template<typename T>
TVector<T> TVector<T>::operator-(const TVector<T>& tmp)
{
    if (this->size != tmp.size)
        throw "!size";
    TVector<T> rez(this->size);
    for (int i = 0; i < this->size; i++)
        rez.arr[i] = this->arr[i] - tmp.arr[i];
    return rez;
}

template<typename T>
T TVector<T>::operator*(const TVector& tmp)
{
    if (this->size != tmp.size)
        throw "!size";
    T rez = 0;
    for (int i = 0; i < this->size; i++)
        rez += this->arr[i] * tmp.arr[i];
    return rez;
}

template<typename T>
bool TVector<T>::operator==(const TVector<T>& tmp)const
{
    if (this->size != tmp.size)
        return false;
    for (int i = 0; i < tmp.size; i++)
        if (this->arr[i] != tmp.arr[i])
            return false;
    return true;
}

template<typename T>
bool TVector<T>::operator!=(const TVector<T>& tmp)const
{
    if (this->size != tmp.size)
        return true;
    for (int i = 0; i < this->size; i++)
        if (this->arr[i] != tmp.arr[i])
            return true;
    return false;
}

template<typename T>
T& TVector<T>::operator[](int i)
{
    if ((i < 0) || (i >= this->size))
        throw "No elem";
    return this->arr[i];
}

template<typename T>
const T& TVector<T>::operator[](int i) const
{
    if ((i < 0) || (i >= this->size))
        throw "No elem";
    return this->arr[i];
}

template<typename T>
int TVector<T>::GetSI()const
{
    return this->startindex;
}

template<typename T>
int TVector<T>::GetSize()const
{
    return this->size;
}