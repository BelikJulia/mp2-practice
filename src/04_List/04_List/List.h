#pragma once
#include <iostream>
using namespace std;

template <class Tkey, class TData>
class TNode
{
public:
    Tkey key;
    TData* pData;
    TNode* pNext;
    TNode();
    TNode(const TNode&);
    TNode(Tkey, TData*);
    ~TNode();

    friend ostream& operator<<(ostream& out, TNode<Tkey, TData>& node)
    {
        out << node.key << " - " << node.pData[0];
        return out;
    }
};


template <class Tkey, class TData>
TNode<Tkey, TData>::TNode()
{
    pData = new TData;
    pNext = NULL;
}

template <class Tkey, class TData>
TNode<Tkey, TData>::TNode(const TNode<Tkey, TData>& tmp)
{
    key = tmp.key;
    pData = new TData;
    pData = tmp.pData;
    pNext = NULL;
}

template <class Tkey, class TData>
TNode<Tkey, TData>::TNode(Tkey _key, TData* _data)
{
    key = _key;
    pData = new TData(*_data);
    pNext = NULL;
}

template <class Tkey, class TData>
TNode<Tkey, TData>::~TNode()
{
    delete pData;
}

template <class Tkey, class TData>
class TList
{
private:
    TNode<Tkey, TData>* pFirst;
    TNode<Tkey, TData>* pPrev;
    TNode<Tkey, TData>* pCurr;
    TNode<Tkey, TData>* pNext;
public:
    TList();
    TList(const TList& list);
    TList(TNode<Tkey, TData>* tmp);
    ~TList();

    bool IsEnded()const;
    void Next();
    void Reset();

    TNode<Tkey, TData>* Search(Tkey _key);
    void Back(Tkey _key, TData* pData);
    void Push(Tkey _key, TData* pData);
    void InsertAfter(TData* _pData, Tkey _key, Tkey _keys);
    void InsertBefore(TData* _pData, Tkey _key, Tkey _keys);
    void Remove(Tkey _key);

    friend ostream& operator<<(ostream& out, TList<Tkey, TData>& list)
    {
        list.Reset();
        while (!(list.IsEnded()))
        {
            //out << list.pCurr->key << " - " << list.pCurr->pData << endl;
            out << (*list.pCurr) << endl;
            list.Next();
        }
        return out;
    }
};

template <class Tkey, class TData>
TList<Tkey, TData>::TList()
{
    pFirst = NULL;
    pPrev = NULL;
    pCurr = NULL;
    pNext = NULL;
}

template <class Tkey, class TData>
TList<Tkey, TData>::TList(const TList<Tkey, TData>& list)
{
    pFirst = new TNode<Tkey, TData>(*(list.pFirst));
    pCurr = pFirst;
    TNode<Tkey, TData>* node = list.pFirst;
    node = node->pNext;
    //list.Reset();
    //list.Next();
    while (node != NULL)
    {
        pCurr->pNext = new TNode<Tkey, TData>(*node);
        pCurr = pCurr->pNext;
        node = node->pNext;
        //list.Next();
    }
    Reset();
}

template <class Tkey, class TData>
TList<Tkey, TData>::TList(TNode<Tkey, TData>* tmp)
{
    pFirst = tmp;
    pCurr = pFirst;
    pPrev = NULL;
    pNext = pCurr->pNext;
}

template <class Tkey, class TData>
TList<Tkey, TData>::~TList()
{
    Reset();
    while (!IsEnded())
    {
        delete pCurr->pData;
        Next();
    }
    pFirst = NULL;
}

template <class Tkey, class TData>
bool TList<Tkey, TData>::IsEnded()const
{
    return (pCurr == NULL);
}

template <class Tkey, class TData>
void TList<Tkey, TData>::Next()
{
    if (IsEnded())
        return;
    pPrev = pCurr;
    pCurr = pCurr->pNext;
    if (pNext != NULL)
        pNext = pNext->pNext;
}

template <class Tkey, class TData>
void TList<Tkey, TData>::Reset()
{
    if (pFirst != NULL)
    {
        pPrev = NULL;
        pCurr = pFirst;
        pNext = pCurr->pNext;
    }
    else
    {
        pPrev = NULL;
        pCurr = NULL;
        pNext = NULL;
    }
}

template <class Tkey, class TData>
TNode<Tkey, TData>* TList<Tkey, TData>::Search(Tkey _key)
{
    Reset();
    while ((!IsEnded()) && (pCurr->key != _key))
        Next();
    if (IsEnded())
        return 0;
    return pCurr;
}

template <class Tkey, class TData>
void TList<Tkey, TData>::Back(Tkey _key, TData* _pData)
{
    if (pFirst == NULL)
    {
        pFirst = new TNode<Tkey, TData>(_key, _pData);
        pCurr = pFirst;
    }
    else
    {
        TNode<Tkey, TData>* pprev = pPrev;
        TNode<Tkey, TData>* pcurr = pCurr;
        TNode<Tkey, TData>* pnext = pNext;
        while (!IsEnded())
            Next();
        pCurr = new TNode<Tkey, TData>(_key, _pData);
        pPrev->pNext = pCurr;
        pPrev = pprev;
        pCurr = pcurr;
        pNext = pnext;
    }
}

template <class Tkey, class TData>
void TList<Tkey, TData>::Push(Tkey _key, TData* _pData)
{
    TNode<Tkey, TData>* tmp = new TNode<Tkey, TData>(_key, _pData);
    tmp->pNext = pFirst;
    pFirst = tmp;
}

template <class Tkey, class TData>
void TList<Tkey, TData>::InsertAfter(TData* _pData, Tkey _keyn, Tkey _keys)
{
    if (pFirst == NULL)
        throw "er";
    if (Search(_keys) == 0)
        return;
    TNode<Tkey, TData>* pprev = pPrev;
    TNode<Tkey, TData>* pcurr = pCurr;
    TNode<Tkey, TData>* pnext = pNext;
    this->pCurr = Search(_keys);
    TNode<Tkey, TData>* tmp = new TNode<Tkey, TData>(_keyn, _pData);
    tmp->pNext = pNext;
    pCurr->pNext = tmp;
    pPrev = pprev;
    pCurr = pcurr;
    pNext = pnext;
}

template <class Tkey, class TData>
void TList<Tkey, TData>::InsertBefore(TData* _pData, Tkey _key, Tkey _keys)
{
    if (pFirst == NULL)
        throw "er";
    if (Search(_keys) == 0)
        return;
    if (pFirst->key == _keys)
    {
        TNode<Tkey, TData>* tmp = new TNode<Tkey, TData>(_key, _pData);
        tmp->pNext = pFirst;
        pFirst = tmp;
        return;
    }
    TNode<Tkey, TData>* pprev = pPrev;
    TNode<Tkey, TData>* pcurr = pCurr;
    TNode<Tkey, TData>* pnext = pNext;
    pCurr = Search(_keys);
    TNode<Tkey, TData>* tmp = new TNode<Tkey, TData>(_key, _pData);
    tmp->pNext = /*this->pÑurr*/Search(_keys);
    /*Search(_keys)*/pPrev->pNext = tmp;
    pPrev = pprev;
    pCurr = pcurr;
    pNext = pnext;
}

template <class Tkey, class TData>
void TList<Tkey, TData>::Remove(Tkey _key)
{
    if (pFirst == NULL)
        throw "er";
    if (Search(_key) == 0)
        return;
    if (pFirst->key == _key)
    {
        delete pFirst->pData;
        pFirst = pFirst->pNext;
        return;
    }
    pCurr = Search(_key);
    pPrev->pNext = pCurr->pNext;
    pCurr->key = 0;
    delete pCurr->pData;
    pCurr->pNext = NULL;
    pCurr = pNext;
    pNext = pNext->pNext;
}
