#ifndef LIST_H
#define LIST_H
#include <iostream>
#include "log.h"

#define AL_START_HEAD 0
#define AL_START_TAIL 1
namespace list
{

template <typename T>
class ListNode
{
public:
  ListNode *m_pPrev;
  ListNode *m_pNext;
  T m_nValue;

public:
  ListNode(const T &v) : m_nValue(v),
                         m_pPrev(nullptr),
                         m_pNext(nullptr)
  {
    LOG(Info) << "class ListNode construrct\n";
  }
  ListNode *getPrev() { return m_pPrev; }
  ListNode *getNext() { return m_pNext; }
  ListNode *getValue() { return m_nValue; }

  void setPrev(ListNode *node) { m_pPrev = node; }
  void setNext(ListNode *node) { m_pNext = node; }
  void setValue(const T &v) { m_nValue = m_nValue; }
  ~ListNode()
  {
    std::cout << "delete node:" << m_nValue << std::endl;
    LOG(Info) << "class ListNode destory\n";
  }
};

template <typename T>
class List
{
public:
  size_t m_nLen;
  ListNode<T> *m_pHead;
  ListNode<T> *m_pTail;

public:
  List();
  size_t getLen() { return m_nLen; }
  bool insertNode(ListNode<T> *, ListNode<T> *, int);
  bool deleteNode(ListNode<T> *);
  bool addNodeHead(ListNode<T> *);
  bool addNodeTail(ListNode<T> *);
  List dupLict();
  ListNode<T> *findNode(const T &m_nValue);
  ListNode<T> *findNodeIndex(long index);
  ~List();
};

template <typename T>
class ListIter
{
public:
  List<T> *m_pList;
  ListNode<T> *m_pNext;
  int m_nDirction;

public:
  ListIter(List<T> *list, int di);
  void listRewindHead();
  void listRewindTail();
  ListNode<T> *getListNext();
  ~ListIter()
  {
    m_pList = m_pNext = nullptr;
  }
};

// List api-------------------
template <typename T>
List<T>::List()
{
  m_nLen = 0;
  m_pHead = nullptr;
  m_pTail = nullptr;
  LOG(Info) << "class List construrct\n";
}

template <typename T>
bool List<T>::insertNode(ListNode<T> *newnode, ListNode<T> *oldnode, int after)
{

  if (after)
  {
    ListNode<T> *oldnext = oldnode->m_pNext;
    newnode->m_pNext = oldnext;
    newnode->m_pPrev = oldnode;
    oldnode->m_pNext = newnode;
    if (oldnext)
      oldnext->m_pPrev = newnode;
    if (m_pTail == oldnode)
      m_pTail = newnode;
  }
  else
  {
    ListNode<T> *oldprev = oldnode->m_pPrev;
    newnode->m_pPrev = oldprev;
    newnode->m_pNext = oldnode;
    oldnode->m_pPrev = newnode;
    if (oldprev)
      oldprev->m_pNext = newnode;
    if (m_pHead == oldnode)
      m_pHead = newnode;
  }

  m_nLen++;
  return true;
}

template <typename T>
bool List<T>::deleteNode(ListNode<T> *node)
{

  if (node->m_pPrev)
    node->m_pPrev->m_pNext = node->m_pNext;
  else //delete head
    m_pHead = node->m_pNext;

  if (node->m_pNext)
    node->m_pNext->m_pPrev = node->m_pPrev;
  else //delete tail
    m_pTail = node->m_pPrev;

  m_nLen--;
  return true;
}

template <typename T>
bool List<T>::addNodeHead(ListNode<T> *node)
{

  if (getLen() == 0)
  {
    m_pHead = m_pTail = node;
    node->m_pPrev = nullptr;
    node->m_pNext = nullptr;
  }
  else
  {
    node->m_pPrev = nullptr;
    m_pHead->m_pPrev = node;
    node->m_pNext = m_pHead;
    m_pHead = node;
  }
  m_nLen++;
  return true;
}

template <typename T>
bool List<T>::addNodeTail(ListNode<T> *node)
{
  if (getLen() == 0)
  {
    m_pHead = m_pTail = node;
    node->m_pPrev = node->m_pNext = nullptr;
  }
  else
  {
    node->m_pNext = nullptr;
    m_pTail->m_pNext = node;
    node->m_pPrev = m_pTail;
    m_pTail = node;
  }
  m_nLen++;
  return true;
}

template <typename T>
List<T> List<T>::dupLict()
{
}

template <typename T>
ListNode<T> *List<T>::findNode(const T &v)
{
  ListNode<T> *res;
  res = m_pHead;
  while (res != nullptr)
  {
    if (res->m_nValue == v)
      break;
    else
    {
      res = res->m_pNext;
    }
  }

  return res;
}

template <typename T>
ListNode<T> *List<T>::findNodeIndex(long index)
{
  ListNode<T> *res = nullptr;
  if (index >= 0)
  {
    if (index >= m_nLen)
      return nullptr;
    res = m_pHead;
    while (index)
    {
      index--;
      res = res->m_pNext;
    }
  }
  else
  {
    index = -index - 1;
    if (index >= m_nLen)
      return nullptr;
    res = m_pTail;
    while (index)
    {
      index--;
      res = res->m_pPrev;
    }
  }

  return res;
}

template <typename T>
List<T>::~List()
{
  size_t len = getLen();
  ListNode<T> *cur = m_pHead, *next = nullptr;

  while (len)
  {
    len--;
    next = cur->m_pNext;
    delete cur;
    cur = next;
  }
  LOG(Info) << "class List destory\n";
}
//end List

//ListIter  api--------
template <typename T>
ListIter<T>::ListIter(List<T> *list, int di)
{
  m_pList = list;
  m_nDirction = di;
  if (di == AL_START_HEAD)
    m_pNext = list->m_pHead;
  else
    m_pNext = list->m_pTail;
}

template <typename T>
void ListIter<T>::listRewindHead()
{
  m_pNext = m_pList->m_pHead;
  m_nDirction = AL_START_HEAD;
}

template <typename T>
void ListIter<T>::listRewindTail()
{
  m_pNext = m_pList->m_pTail;
  m_nDirction = AL_START_TAIL;
}

template <typename T>
ListNode<T> *ListIter<T>::getListNext()
{
  ListNode<T> *res = m_pNext;

  if (res != nullptr)
  {
    if (m_nDirction == AL_START_HEAD)
      m_pNext = res->m_pNext;
    else
      m_pNext = res->m_pPrev;
  }

  return res;
}

//end ListIter
}

#endif //DLIST_H