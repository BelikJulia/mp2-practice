#pragma once
#include <iostream>
using namespace std;

template <class Tkey, class TData>
class TNode
{
public:
    Tkey key;
    TData pData;
    TNode* pNext;
    TNode();
    TNode(const TNode&);
    TNode(Tkey, TData, TNode*  next = 0);
    ~TNode();

    friend ostream& operator<<(ostream& out, TNode<Tkey, TData>& node)
    {
        out << node.key << " - " << node.pData;
        return out;
    }
};

template <class Tkey, class TData>
TNode<Tkey, TData>::TNode()
{
    pNext = NULL;
}
template <class Tkey, class TData>
TNode<Tkey, TData>::TNode(const TNode<Tkey, TData>& tmp)
{
    key = tmp.key;
    pData = tmp.pData;
    pNext = NULL;
}
template <class Tkey, class TData>
TNode<Tkey, TData>::TNode(Tkey _key, TData _data, TNode* next)
{
    key = _key;
    pData = _data;
    pNext = next;
}
template <class Tkey, class TData>
TNode<Tkey, TData>::~TNode()
{
    key = NULL;
    pData = NULL;
}


template <class Tkey, class TData>
class TList
{
public:
    TNode<Tkey, TData>* pFirst;
    TNode<Tkey, TData>* pPrev;
    TNode<Tkey, TData>* pCurr;
    TNode<Tkey, TData>* pNext;

    TList();
    TList(const TList<Tkey, TData>& list);
    TList(TNode<Tkey, TData>* tmp);
    ~TList();

    bool IsEnded()const;
    void Next();
    void Reset();

    TNode<Tkey, TData>* Search(Tkey key);
    void Back(const TNode<Tkey, TData>&);
    void Push(const TNode<Tkey, TData>&);
    void InsertAfter(const TNode<Tkey, TData>&, Tkey key);
    void InsertBefore(const TNode<Tkey, TData>&, Tkey key);
    void Remove(Tkey key);

    friend ostream& operator<<(ostream& out, TList<Tkey, TData>& list)
    {
        list.Reset();
        while (!(list.IsEnded()))
        {
            out << list->pCurr << endl;
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
    if (list.pFirst == NULL)
    {
        pFirst = NULL;
        pPrev = NULL;
        pCurr = NULL;
        pNext = NULL;
        return;
    }
    pFirst = new TNode<Tkey, TData>(*(list.pFirst));
    pCurr = pFirst;
    TNode<Tkey, TData>* node = list.pFirst;
    node = node->pNext;
    while (node != NULL)
    {
        pCurr->pNext = new TNode<Tkey, TData>(*node);
        pCurr = pCurr->pNext;
        node = node->pNext;
    }
    Reset();
}
template <class Tkey, class TData>
TList<Tkey, TData>::TList(TNode<Tkey, TData>* list)
{
    pFirst = new TNode<Tkey, TData>(*list);
    pCurr = pFirst;
    TNode<Tkey, TData>* node = list;
    node = node->pNext;
    while (node != NULL)
    {
        pCurr->pNext = new TNode<Tkey, TData>(*node);
        pCurr = pCurr->pNext;
        node = node->pNext;
    }
    Reset();
}
template <class Tkey, class TData>
TList<Tkey, TData>::~TList()
{
    Reset();
    while (!IsEnded())
    {
        Next();
        delete pPrev;
    }
    delete pCurr;
    pFirst = NULL;
    pCurr = NULL;
    pPrev = NULL;
    pNext = NULL;
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
    pPrev = NULL;
    pCurr = pFirst;
    if (pFirst != NULL)
    {
        pNext = pCurr->pNext;
    }
    else
    {
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
    {
        Reset();
        return NULL;
    }
    return pCurr;
}
template <class Tkey, class TData>
void TList<Tkey, TData>::Back(const TNode<Tkey, TData>& tmp)
{
    if (pFirst == NULL)
    {
        pFirst = new TNode<Tkey, TData>(tmp);
        pCurr = pFirst;
    }
    else
    {
        TNode<Tkey, TData>* pprev = pPrev;
        TNode<Tkey, TData>* pcurr = pCurr;
        TNode<Tkey, TData>* pnext = pNext;
        while (!IsEnded())
            Next();
        pCurr = new TNode<Tkey, TData>(tmp);
        pPrev->pNext = pCurr;

        pPrev = pprev;
        pCurr = pcurr;
        pNext = pnext;
    }
}
template <class Tkey, class TData>
void TList<Tkey, TData>::Push(const TNode<Tkey, TData>& tmp)
{
    TNode<Tkey, TData>* tmp1 = new TNode<Tkey, TData>(tmp.key, tmp.pData, pFirst);
    if (pCurr == pFirst)
    {
        pPrev = tmp1;
    }
    pFirst = tmp1;
}
template <class Tkey, class TData>
void TList<Tkey, TData>::InsertAfter(const TNode<Tkey, TData>& s, Tkey n)
{
    if (pFirst == NULL)
        throw "er";
    TNode<Tkey, TData>* pprev = pPrev;
    TNode<Tkey, TData>* pcurr = pCurr;
    TNode<Tkey, TData>* pnext = pNext;

    if (Search(n) == NULL)
    {
        pPrev = pprev;
        pCurr = pcurr;
        pNext = pnext;
        return;
    }
    TNode<Tkey, TData>* tmp = new TNode<Tkey, TData>(s.key, s.pData, pNext);
    pCurr->pNext = tmp;

    pPrev = pprev;
    pCurr = pcurr;
    pNext = pnext;
}
template <class Tkey, class TData>
void TList<Tkey, TData>::InsertBefore(const TNode<Tkey, TData>& s, Tkey n)
{
    if (pFirst == NULL)
        throw "er";
    TNode<Tkey, TData>* pprev = pPrev;
    TNode<Tkey, TData>* pcurr = pCurr;
    TNode<Tkey, TData>* pnext = pNext;

    if (Search(n) == NULL)
    {
        pPrev = pprev;
        pCurr = pcurr;
        pNext = pnext;
        return;
    }

    if (pFirst == pCurr)
    {
        TNode<Tkey, TData>* tmp = new TNode<Tkey, TData>(s.key, s.pData, pFirst);
        if (pcurr == pFirst)
        {
            pPrev = tmp;
        }
        else
        {
            pPrev = pprev;
            pCurr = pcurr;
            pNext = pnext;
        }
        pFirst = tmp;
        return;
    }

    TNode<Tkey, TData>* tmp = new TNode<Tkey, TData>(s.key, s.pData, pCurr);
    pPrev->pNext = tmp;

    pPrev = pprev;
    pCurr = pcurr;
    pNext = pnext;
}
template <class Tkey, class TData>
void TList<Tkey, TData>::Remove(Tkey s)
{
    if (pFirst == NULL)
        throw "er";
    TNode<Tkey, TData>* pprev = pPrev;
    TNode<Tkey, TData>* pcurr = pCurr;
    TNode<Tkey, TData>* pnext = pNext;

    if (Search(s) == 0)
    {
        pPrev = pprev;
        pCurr = pcurr;
        pNext = pnext;
        return;
    }
    if (pFirst == pCurr)
    {
        if (pcurr == pFirst)
        {
            if (pNext == 0)
            {
                pNext = pNext->pNext;
            }
            pCurr = pNext;
            pPrev->pNext = pCurr;
        }
        delete pFirst;
        pFirst = pNext;

        return;
    }

    if (pcurr == pCurr)
    {
        delete pCurr;
        pCurr = pnext;
        pPrev->pNext = pCurr;
        if (pNext == 0)
        {
            pNext = pNext->pNext;
        }
        return;
    }

    pPrev->pNext = pCurr->pNext;
    delete pCurr;
    pCurr = pNext;
    if (pNext == 0)
    {
        pNext = pNext->pNext;
    }
    pPrev = pprev;
    pCurr = pcurr;
    pNext = pnext;
}
