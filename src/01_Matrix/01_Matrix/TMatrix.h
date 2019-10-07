#pragma once
#include "TVector.h"

template<typename T>
class TMatrix : public TVector<TVector<T> >
{
public:
    TMatrix(int _size);
    TMatrix(const TMatrix& tmp);
    TMatrix(const TVector<TVector<T> >& tmp);
    ~TMatrix();

    TMatrix& operator=(const TMatrix& tmp);// const;
    TMatrix operator+(const T a);
    TMatrix operator-(const T a);
    TMatrix operator*(const T a);
    TMatrix operator+(const TMatrix& tmp);
    TMatrix operator-(const TMatrix& tmp);
    TMatrix operator*(const TMatrix& tmp);
    TVector<T> operator*(const TVector<T>& tmp);
    bool operator==(const TMatrix& tmp)const;
    bool operator!=(const TMatrix& tmp)const;

    friend istream& operator>>(istream& in, TMatrix<T>& m)
    {
        for (int i = 0; i < m.size; i++)
            in >> m.arr[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TMatrix<T>& m)
    {
        /*for (int i = 0; i < m.size; i++)
            out << m[i] << endl;
        return out;*/
        for (int j = 0; j < m.GetSize(); j++)
        {
            for (int i = 0; i < (m.GetSize() - m.arr[j].GetSize()); i++)
                out << "0 ";
            for (int i = 0; i < m.arr[j].GetSize(); i++)
                out << m.arr[j][i] << " ";
            out << endl;
        }
        return out;
    }
};

template<typename T>
TMatrix<T>::TMatrix(int _size):TVector<TVector<T> >(_size)
{    
    this->size = _size; 
    for (int i = 0; i < this->size; i++)
    {
         this->arr[i] = TVector<T>(this->size - i, i);
    }
}

template<typename T>
TMatrix<T>::TMatrix(const TMatrix<T>& tmp):TVector<TVector<T> >(tmp)
{
    this->size = tmp.size;
    for (int i = 0; i < this->size; i++)
        this->arr[i] = TVector<T>(tmp.arr[i]);
}

template<typename T>
TMatrix<T>::TMatrix(const TVector<TVector<T> >& tmp):TVector<TVector<T> >(tmp)
{
    if ((sqrt(tmp.size * 8 + 1) - 1) % 2 == 1)
        throw "!size";
    this->size = (sqrt(tmp.size * 8 + 1) - 1) / 2;
    int s = 0;
    for (int i = 0; i < this->size; i++)
    {
        this->arr[i] = TVector<T>(this->size - i, i);
        for (int j = 0; j < this->size - i; j++)
            this->arr[i][j] = tmp.arr[s++];//[][]
    }
}

template<typename T>
TMatrix<T>::~TMatrix() {}

template<typename T>
TMatrix<T>& TMatrix<T>::operator=(const TMatrix& tmp)//const
{
    if (*this == tmp)
        return *this;
    if (this->size != tmp.size)
    {
        this->size = tmp.size; 
        delete this->arr;
        this->arr = new TVector<T>[tmp.size];
    } 
    for (int i = 0; i < this->size; i++)
        this->arr[i] = tmp.arr[i];
    return *this;
}

template<typename T>
TMatrix<T> TMatrix<T>::operator+(const T a)
{
    TMatrix<T> rez(this->size);
    for (int i = 0; i < this->size; i++)
        rez.arr[i] = this->arr[i] + a;
    return rez;
}

template<typename T>
TMatrix<T> TMatrix<T>::operator-(const T a)
{
    TMatrix<T> rez(this->size);
    for (int i = 0; i < this->size; i++)
        rez.arr[i] = this->arr[i] - a;
    return rez;
}

template<typename T>
TMatrix<T> TMatrix<T>::operator*(const T a)
{
    TMatrix<T> rez(this->size);
    for (int i = 0; i < this->size; i++)
        rez.arr[i] = this->arr[i] * a;
    return rez;
}

template<typename T>
TMatrix<T> TMatrix<T>::operator+(const TMatrix& tmp)
{
    if (this->size != tmp.size)
        throw "!size";
    TMatrix<T> rez(this->size);
    for (int i = 0; i < this->size; i++)
        rez.arr[i] = this->arr[i] + tmp.arr[i];
    return rez;
}

template<typename T>
TMatrix<T> TMatrix<T>::operator-(const TMatrix& tmp)
{
    if (this->size != tmp.size)
        throw "!size";
    TMatrix<T> rez(this->size);
    for (int i = 0; i < this->size; i++)
        rez.arr[i] = this->arr[i] - tmp.arr[i];
    return rez;
}

template<typename T>
bool TMatrix<T>::operator==(const TMatrix& tmp)const
{
    if (this->size != tmp.size)
        return false; 
    for (int i = 0; i < this->size; i++)
        if (this->arr[i] != tmp.arr[i])
            return false;
    return true;
}

template<typename T>
bool TMatrix<T>::operator!=(const TMatrix& tmp)const
{
    if (this->size != tmp.size)
        return true;
    for (int i = 0; i < this->size; i++)
        if (this->arr[i] != tmp.arr[i])
            return true;
    return false;
}

template<typename T>
TMatrix<T> TMatrix<T>::operator*(const TMatrix& tmp)
{
    if (this->size != tmp.size)
        throw "!size";
    TMatrix<T> res(this->size);
    res = res * 0;
    for (int i = 0; i < this->size; i++)
        for (int j = this->arr[i].GetSI(); j < this->size; j++)
            for (int k = i; k <= j; k++)
                res.arr[i][j - i] += this->arr[i][k - i] * tmp.arr[k][j - k];
    return res;
}

template<typename T>
TVector<T> TMatrix<T>::operator*(const TVector<T>& tmp)
{
    if (this->GetSize() != tmp.GetSize())
        throw "!size";
    TVector<T> rez(this->size);
    rez = rez * 0;
    for (int i = 0; i < this->size; i++)
        for (int j = 0; j < this->arr[i].GetSize(); j++)
            rez[i] += this->arr[i][j] * tmp[i + j];
    return rez;
}