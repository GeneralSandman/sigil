#ifndef LIST_H
#define LIST_H
#include <iostream>
#include "log.h"

#define AL_START_HEAD 0
#define AL_START_TAIL 1

#define After 0
#define Before 1

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
  std::string m_nName;
  size_t m_nLen;
  ListNode<T> *m_pHead;
  ListNode<T> *m_pTail;

  bool m_fInsertNode(ListNode<T> *, ListNode<T> *, int);
  bool m_fDeleteNode(ListNode<T> *);
  bool m_fAddNodeHead(ListNode<T> *);
  bool m_fAddNodeTail(ListNode<T> *);
  bool m_fDeleteNodeHead();
  bool m_fDeleteNodeTail();

  ListNode<T> *m_fFindNode(const T &m_nValue);
  ListNode<T> *m_fFindNodeIndex(long index);

public:
  List(const std::string &);
  size_t getLen() { return m_nLen; }
  bool insert(T, T, int flag = 0);
  bool dele(T);
  bool add_head(T);
  bool add_tail(T);
  T pop_head();
  T pop_tail();
  bool clear();

  List dupLict();
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
List<T>::List(const std::string &name)
{
  m_nName = name;
  m_nLen = 0;
  m_pHead = nullptr;
  m_pTail = nullptr;
  LOG(Info) << "class List construrct\n";
}

template <typename T>
bool List<T>::m_fInsertNode(ListNode<T> *newnode, ListNode<T> *oldnode, int after)
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
bool List<T>::m_fDeleteNode(ListNode<T> *node)
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
  delete node;
  node = nullptr;
  return true;
}

template <typename T>
bool List<T>::m_fAddNodeHead(ListNode<T> *node)
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
bool List<T>::m_fAddNodeTail(ListNode<T> *node)
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
bool List<T>::m_fDeleteNodeHead()
{
  if (m_nLen == 0)
    return false;
  m_fDeleteNode(m_pHead);
}
template <typename T>
bool List<T>::m_fDeleteNodeTail()
{
  if (m_nLen == 0)
    return false;
  m_fDeleteNode(m_pTail);
}

template <typename T>
List<T> List<T>::dupLict()
{
}

template <typename T>
ListNode<T> *List<T>::m_fFindNode(const T &v)
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
ListNode<T> *List<T>::m_fFindNodeIndex(long index)
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
bool List<T>::insert(T newvalue, T oldvalue, int flag)
{
  ListNode<T> *newnode =
      new ListNode<T>(newvalue);
  ListNode<T> *oldnode = m_fFindNode(oldvalue);
  if (oldnode == nullptr)
    return false;
  return m_fInsertNode(newnode, oldnode, flag);
}
template <typename T>
bool List<T>::dele(T value)
{
  ListNode<T> *node = m_fFindNode(value);
  return m_fDeleteNode(node);
}
template <typename T>
bool List<T>::add_head(T value)
{
  ListNode<T> *newnode =
      new ListNode<T>(value);
  return m_fAddNodeHead(newnode);
}
template <typename T>
bool List<T>::add_tail(T value)
{
  ListNode<T> *newnode =
      new ListNode<T>(value);
  return m_fAddNodeTail(newnode);
}
template <typename T>
T List<T>::pop_head()
{
  if (m_nLen)
  {
    T res = m_pHead->m_nValue;
    m_fDeleteNodeHead();
    return res;
  }
}

template <typename T>
T List<T>::pop_tail()
{
  if (m_nLen)
  {
    T res = m_pTail->m_nValue;
    m_fDeleteNodeTail();
    return res;
  }
}

template <typename T>
bool List<T>::clear()
{
  while (m_nLen)
  {
    m_fDeleteNodeHead();
  }
  if (!m_nLen)
    return true;
  else
    return false;
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

#include <string>
#include <deque>
bool lpushCommand(std::deque<std::string> &args);
bool rpushCommand(std::deque<std::string> &args);
bool lpopCommand(std::deque<std::string> &args);
bool rpopCommand(std::deque<std::string> &args);
bool llenCommand(std::deque<std::string> &args);
bool lindexCommand(std::deque<std::string> &args);
bool linsertCommand(std::deque<std::string> &args);
bool lrangeCommand(std::deque<std::string> &args);
bool lremCommand(std::deque<std::string> &args);
bool lclearCommand(std::deque<std::string> &args);

#endif //DLIST_H