#ifndef Rb_TREE
#define Rb_TREE
#include <iostream>
#include <vector>

#include "log.h"


typedef enum { red,
               black } color;
class RbTree;
class RbTreeNode
{
private:
  color m_nColor;
  int m_nValue;
  RbTreeNode *m_pParent;
  RbTreeNode *m_pLeft;
  RbTreeNode *m_pRight;

public:
  RbTreeNode(const int &value, color co = red)
  {
    m_nColor = co;
    m_nValue = value;
    m_pParent = m_pLeft = m_pRight = nullptr;
    LOG(Debug) << "class RbTreeNode constructor" << std::endl;
  }
  ~RbTreeNode()
  {
    LOG(Debug) << "class RbTreeNode destructor" << std::endl;
  }
  RbTreeNode *getGParent(void)
  {
    if (getParent())
      return getParent()->getParent();
    else
      return nullptr;
  }

  RbTreeNode *getUncle(void)
  {
    RbTreeNode *parent = getParent(), *gparent = getGParent();
    if (gparent)
    {
      if (parent == gparent->getLeft())
        return gparent->getRight();
      else if (parent == gparent->getRight())
        return gparent->getLeft();
      else
        return nullptr;
    }

    else
      return nullptr;
  }

  friend class RbTree;
};

class RbTree
{
private:
  RbTreeNode *m_pRoot;
  int m_nNumber;
  RbTreeNode *m_fFindNode(const int &);
  void m_fFixAfterInsert(RbTreeNode *);
  void m_fFixAfterDelete(RbTreeNode *, RbTreeNode *);
  void m_fInsertNode(const int &, RbTreeNode *);
  void m_fDeleteNode(RbTreeNode *);
  RbTreeNode *m_fFindLeftSubTreeMaxNode(RbTreeNode *);
  RbTreeNode *m_fFindRightSubTreeMinNode(RbTreeNode *);
  void m_fPreorder(RbTreeNode *);//
  void m_fInorder(RbTreeNode *);//
  void m_fPostorder(RbTreeNode *);//
  void m_fLevel(std::vector<std::vector<int>> &result, RbTreeNode *node, int level);//
  void m_fDisplay(std::vector<std::string> &, RbTreeNode *, int);//
  void m_fDeleteAllNode(RbTreeNode *node, int &);

  int m_fGetHeight(RbTreeNode *);//

  void m_fLeftRotate(RbTreeNode *node);
  void m_fRightRotate(RbTreeNode *node);
  void m_fRoatLeftLeft(RbTreeNode *node);
  void m_fRoatLeftRight(RbTreeNode *node);
  void m_fRoatRightLeft(RbTreeNode *node);
  void m_fRoatRightRight(RbTreeNode *node);

public:
  RbTree();
  ~RbTree();
  bool FindNode(const int &);
  void PrintTreePreorder();//
  void PrintTreeInorder();//
  void PrintTreePostorder();//
  void PrintTreeLevel();//
  void DisplayTree();//
  void InsertNode(const int &);
  void DeleteNode(const int &);
  int getNumber(void);
  bool testBalance(void);//
  void testRoat(void);//
};

#endif