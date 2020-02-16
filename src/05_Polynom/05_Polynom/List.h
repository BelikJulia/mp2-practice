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
{}

template <class TNode>
class TList
{
public://protected:
    TNode/*<Tkey, TData>*/* pFirst;
    TNode/*<Tkey, TData>*/* pPrev;
    TNode/*<Tkey, TData>*/* pCurr;
    TNode/*<Tkey, TData>*/* pNext;
    //public:
    TList();
    TList(const TList& list);
    TList(TNode* tmp);
    ~TList();

    bool IsEnded()const;
    void Next();
    void Reset();

    TNode* Search(TNode);
    void Back(TNode);
    void Push(TNode);
    void InsertAfter(TNode, TNode);
    void InsertBefore(TNode, TNode);
    void Remove(TNode);

    friend ostream& operator<<(ostream& out, TList<TNode>& list)
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

template <class TNode>
TList<TNode>::TList()
{
    pFirst = NULL;
    pPrev = NULL;
    pCurr = NULL;
    pNext = NULL;
}
template <class TNode>
TList<TNode>::TList(const TList<TNode>& list)
{
    pFirst = new TNode(*(list.pFirst));
    pCurr = pFirst;
    TNode* node = list.pFirst;
    node = node->pNext;
    while (node != NULL)
    {
        pCurr->pNext = new TNode/*<Tkey, TData>*/(*node);
        pCurr = pCurr->pNext;
        node = node->pNext;
    }
    Reset();
}
template <class TNode>
TList<TNode>::TList(TNode* list)
{
    pFirst = new TNode/*<Tkey, TData>*/(*list);
    pCurr = pFirst;
    TNode/*<Tkey, TData>*/* node = list;
    node = node->pNext;
    while (node != NULL)
    {
        pCurr->pNext = new TNode/*<Tkey, TData>*/(*node);
        pCurr = pCurr->pNext;
        node = node->pNext;
    }
    Reset();
}
template <class TNode>
TList<TNode>::~TList()
{
    Reset();
    pFirst = NULL;
}
template <class TNode>
bool TList<TNode>::IsEnded()const
{
    return (pCurr == NULL);
}
template <class TNode>
void TList<TNode>::Next()
{
    if (IsEnded())
        return;
    pPrev = pCurr;
    pCurr = pCurr->pNext;
    if (pNext != NULL)
        pNext = pNext->pNext;
}
template <class TNode>
void TList<TNode>::Reset()
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
template <class TNode>
TNode* TList<TNode>::Search(TNode tmp)
{
    Reset();
    while ((!IsEnded()) && (pCurr->key != tmp.key))
        Next();
    if (IsEnded())
    {
        Reset();
        return 0;
    }
    return pCurr;
}
template <class TNode>
void TList<TNode>::Back(TNode tmp)
{
    if (pFirst == NULL)
    {
        pFirst = new TNode(tmp);
        pCurr = pFirst;
    }
    else
    {
        TNode* pprev = pPrev;
        TNode* pcurr = pCurr;
        TNode* pnext = pNext;
        while (!IsEnded())
            Next();
        pCurr = new TNode(tmp);
        pPrev->pNext = pCurr;

        pPrev = pprev;
        pCurr = pcurr;
        pNext = pnext;
    }
}
template <class TNode>
void TList<TNode>::Push(TNode tmp)
{
    TNode* tmp1 = new TNode(tmp.key, tmp.pData, pFirst);
    if (pCurr == pFirst)
    {
        pPrev = tmp1;
    }
    pFirst = tmp1;
}
template <class TNode>
void TList<TNode>::InsertAfter(TNode s, TNode n)
{
    if (pFirst == NULL)
        throw "er";
    TNode* pprev = pPrev;
    TNode* pcurr = pCurr;
    TNode* pnext = pNext;

    if (Search(s.key) == 0)
    {
        pPrev = pprev;
        pCurr = pcurr;
        pNext = pnext;
        return;
    }
    TNode* tmp = new TNode(n.key, n.pData, pNext);
    pCurr->pNext = tmp;

    pPrev = pprev;
    pCurr = pcurr;
    pNext = pnext;
}
template <class TNode>
void TList<TNode>::InsertBefore(TNode s, TNode n)
{
    if (pFirst == NULL)
        throw "er";
    TNode* pprev = pPrev;
    TNode* pcurr = pCurr;
    TNode* pnext = pNext;

    if (Search(s) == 0)
    {
        pPrev = pprev;
        pCurr = pcurr;
        pNext = pnext;
        return;
    }

    if (pFirst == pCurr)
    {
        TNode* tmp = new TNode(n.key, n.pData, pFirst);
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

    TNode* tmp = new TNode(n.key, n.pData, pCurr);
    pPrev->pNext = tmp;

    pPrev = pprev;
    pCurr = pcurr;
    pNext = pnext;
}
template <class TNode>
void TList<TNode>::Remove(TNode s)
{
    if (pFirst == NULL)
        throw "er";
    TNode* pprev = pPrev;
    TNode* pcurr = pCurr;
    TNode* pnext = pNext;

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
