#include <iostream>
#include "rb_tree.h"
#include "log.h"

RbTreeNode *RbTree::m_fFindNode(const int &value)
{
    if (m_pRoot == nullptr)
    {
        return nullptr;
    }

    RbTreeNode *node = m_pRoot;
    while (node)
    {
        if (value < node->m_nValue)
            node = node->m_pLeft;
        else if (value > node->m_nValue)
            node = node->m_pRight;
        else
            break;
    }
    return node;
}

void RbTree::m_fInsertNode(RbTreeNode *newnode)
{
    RbTreeNode *pre = m_pRoot, *insert = m_pRoot;
    int newvalue = newnode->m_nValue;
    while (insert != nullptr)
    {
        pre = insert;
        if (newvalue < insert->m_nValue)
            insert = insert->m_pLeft;
        else if (newvalue > insert->m_nValue)
            insert = insert->m_pRight;
    }

    //make link between newnode and pre
    newnode->m_pParent = pre;
    if (newvalue < pre->m_nValue)
        pre->m_pLeft = newnode;
    else if (newvalue > pre->m_nValue)
        pre->m_pRight = newnode;

    //fix after insert
    m_fFixAfterInsert(newnode);
}

void RbTree::m_fFixAfterInsert(RbTreeNode *node)
{
    RbTreeNode *parent = nullptr, *gparent = nullptr;

    while ((parent = node->m_pParent) != nullptr && parent->m_nColor == red)
    {
        gparent = parent->m_pParent;

        if (parent == gparent->m_pLeft)
        {
            RbTreeNode *uncle = gparent->m_pRight;

            if (uncle != nullptr && uncle->m_nColor == red)
            {
                parent->m_nColor = black;
                uncle->m_nColor = black;
                gparent->m_nColor = red;
                node = gparent;
                continue;
            }

            if (node == parent->m_pRight)
            { //uncle is black && node is parent's right-node
                m_fLeftRotate(parent);
                RbTreeNode *tmp = parent;
                parent = node;
                node = tmp;
            }

            parent->m_nColor = black;
            gparent->m_nColor = red;
            m_fRightRotate(gparent);
        }
        else
        {
            RbTreeNode *uncle = gparent->m_pLeft;

            if (uncle != nullptr && uncle->m_nColor == red)
            {
                parent->m_nColor = black;
                uncle->m_nColor = black;
                gparent->m_nColor = red;
                node = gparent;
                continue;
            }

            if (node == parent->m_pLeft)
            {
                m_fRightRotate(parent);
                RbTreeNode *tmp = parent;
                parent = node;
                node = tmp;
            }

            parent->m_nColor = black;
            gparent->m_nColor = red;
            m_fLeftRotate(gparent);
        }
    }

    m_pRoot->m_nColor = black;
}

// void RbTree::m_fDeleteNode(RbTreeNode *node)
// {
//     RbTreeNode *child, *parent;
//     color color_tmp;
//     if ((node->m_pLeft != null) && (node->m_pRight != null))
//     {
//         RbTreeNode *replace = node;
//         replace = replace->m_pRight;
//         while (replace->m_pLeft != null)
//             replace = replace->m_pLeft;

//         if (node->m_pParent != null)
//         { //要删除的节点不是根节点
//             if (node == node->m_pParent->m_pLeft)
//                 node->m_pParent->m_pLeft = replace;
//             else
//                 node->m_pParent->m_pRight = replace;
//         }
//         else
//         { //否则
//             this->root = replace;
//         }

//         child = replace->m_pRight; //后继节点肯定不存在左子节点！
//         parent = replace->m_pParent;
//         color_tmp = replace->m_nColor; //保存后继节点的颜色
//         if (parent == node)
//         { //后继节点是被删除节点的子节点
//             parent = replace;
//         }
//         else
//         { //否则
//             if (child != null)
//                 child->m_pParent = parent;
//             parent->m_pLeft = child;
//             replace->m_pRight = node->m_pRight;
//             node->m_pRight->m_pParent = replace;
//         }
//         replace->m_pParent = node->m_pParent;
//         replace->m_nColor = node->m_nColor; //保持原来位置的颜色
//         replace->m_pLeft = node->m_pLeft;
//         node->m_pLeft->m_pParent = replace;

//         if (color_tmp == black)
//         {                                     //4. 如果移走的后继节点颜色是黑色，重新修整红黑树
//             m_fFixAfterDelete(child, parent); //将后继节点的child和parent传进去
//         }
//         node = null;
//         return;
//     }
// }

// void RbTree::m_fFixAfterDelete(RbTreeNode *, RbTreeNode *)
// {
//     RbTreeNode *other;

//     while ((node == null ||  node->m_nColor==black && (node != this.root))
//     {
//         if (parent->m_pLeft == node)
//         {                             //node是左子节点，下面else与这里的刚好相反
//             other = parent->m_pRight; //node的兄弟节点
//             if (other->m_nColor == red)
//             { //case1: node的兄弟节点other是红色的
//                 other->m_nColor = black;
//                 parent->m_nColor = red;
//                 m_fLeftRotate(parent);
//                 other = parent->m_pRight;
//             }

//             //case2: node的兄弟节点other是黑色的，且other的两个子节点也都是黑色的
//             if ((other->m_pLeft == null || other->m_pLeft->m_nColor == black) &&
//                 (other->m_pRight == null || other->m_pRight->m_nColor == black))
//             {
//                 setRed(other);
//                 node = parent;
//                 parent = parentOf(node);
//             }
//             else
//             {
//                 //case3: node的兄弟节点other是黑色的，且other的左子节点是红色，右子节点是黑色
//                 if (other->m_pRight == null || other->m_pRight->m_nColor == black)
//                 {
//                     setBlack(other->m_pLeft);
//                     setRed(other);
//                     rightRotate(other);
//                     other = parent->m_pRight;
//                 }

//                 //case4: node的兄弟节点other是黑色的，且other的右子节点是红色，左子节点任意颜色
//                 setColor(other, colorOf(parent));
//                 setBlack(parent);
//                 setBlack(other->m_pRight);
//                 leftRotate(parent);
//                 node = this.root;
//                 break;
//             }
//         }
//         else
//         { //与上面的对称
//             other = parent->m_pLeft;

//             if (isRed(other))
//             {
//                 // Case 1: node的兄弟other是红色的
//                 setBlack(other);
//                 setRed(parent);
//                 rightRotate(parent);
//                 other = parent->m_pLeft;
//             }

//             if ((other->m_pLeft == null || other->m_pLeft->m_nColor == black) &&
//                 (other->m_pRight == null || other->m_pRight->m_nColor == black))
//             {
//                 // Case 2: node的兄弟other是黑色，且other的俩个子节点都是黑色的
//                 setRed(other);
//                 node = parent;
//                 parent = parentOf(node);
//             }
//             else
//             {

//                 if (other->m_pLeft == null || other->m_pLeft->m_nColor == black)
//                 {
//                     // Case 3: node的兄弟other是黑色的，并且other的左子节点是红色，右子节点为黑色。
//                     setBlack(other->m_pRight);
//                     setRed(other);
//                     leftRotate(other);
//                     other = parent->m_pLeft;
//                 }

//                 // Case 4: node的兄弟other是黑色的；并且other的左子节点是红色的，右子节点任意颜色
//                 setColor(other, colorOf(parent));
//                 setBlack(parent);
//                 setBlack(other->m_pLeft);
//                 rightRotate(parent);
//                 node = this.root;
//                 break;
//             }
//         }
//     }
//     if (node != null)
//         setBlack(node);
// }

// RbTreeNode *RbTree::m_fFindLeftSubTreeMaxNode(RbTreeNode *node)
// {
//     RbTreeNode *leftmax = nullptr, *left = node->getLeft();
//     while (left)
//     {
//         leftmax = left;
//         left = left->getRight();
//     }
//     return leftmax;
// }

// RbTreeNode *RbTree::m_fFindRightSubTreeMinNode(RbTreeNode *node)
// {
//     RbTreeNode *rightmin = nullptr, *right = node->getRight();
//     while (right != nullptr)
//     {
//         rightmin = right;
//         right = right->getLeft();
//     }
//     return rightmin;
// }

void RbTree::m_fDeleteAllNode(RbTreeNode *node, int &deleteNumber)
{
    if (node == nullptr)
        return;
    if (node->m_pLeft != nullptr)
        m_fDeleteAllNode(node->m_pLeft, deleteNumber);
    if (node->m_pRight != nullptr)
        m_fDeleteAllNode(node->m_pRight, deleteNumber);
    if (node->m_pLeft == nullptr && node->m_pRight == nullptr)
    {
        RbTreeNode *parent = node->m_pParent;
        if (parent != nullptr)
        {
            if (node->m_nValue < parent->m_nValue)
                parent->m_pLeft = nullptr;
            else
                parent->m_pRight = nullptr;
        }
        deleteNumber++;
        m_nNumber--;
        delete node;
        node = nullptr;
    }
}

RbTree::RbTree()
{
    m_pRoot = nullptr;
    m_nNumber = 0;
    LOG(Debug) << "class RbTree constructor\n";
}

RbTree::~RbTree()
{
    int deleteNumber = 0;
    int number = getNumber();
    m_fDeleteAllNode(m_pRoot, deleteNumber);
    if (number == deleteNumber && getNumber() == 0)
        std::cout << "all node are deleted\n";
    else
        std::cout << "delete tree failed\n";

    LOG(Debug) << "class RbTree destructor\n";
}

bool RbTree::find(const int &value)
{
    RbTreeNode *node = m_fFindNode(value);
    if (node != nullptr)
        return true;
    else
        return false;
}

void RbTree::insert(const int &value)
{
    RbTreeNode *newnode = new RbTreeNode(value);
    if (m_pRoot == nullptr)
    {
        m_pRoot = newnode;
        m_pRoot->m_nColor = black;
    }
    else
    {
        m_fInsertNode(newnode);
    }
    m_nNumber++;
}

// void RbTree::deleteNode(const int &value)
// {
//     RbTreeNode *node = m_fFindNode(value);
//     if (node != nullptr)
//     {
//         m_fDeleteNode(node);
//         m_nNumber--;
//     }
//     else
//     {
//         std::cout << "don't exists this value\n";
//     }
// }

void RbTree::m_fLeftRotate(RbTreeNode *node)
{
    /* 
		 * left rotate function
		 *     p                       p 
		 *    /                       / 
		 *   x                       y 
		 *  / \                     / \ 
		 * lx  y      ----->       x  ry 
		 *    / \                 / \ 
		 *   ly ry               lx ly 
		 */
    RbTreeNode *x = node;         //must
    RbTreeNode *p = x->m_pParent; //may be
    RbTreeNode *lx = x->m_pLeft;  //may be
    RbTreeNode *y = x->m_pRight;  //must
    RbTreeNode *ly = y->m_pLeft;  //may be
    RbTreeNode *ry = y->m_pRight; //may be

    //first step:make link between x and ly
    x->m_pRight = ly;
    if (ly != nullptr)
        ly->m_pParent = x;

    //second step:make link between y and p
    y->m_pParent = p;
    if (p != nullptr)
    {
        if (x == p->m_pLeft)
            p->m_pLeft = y;
        else
            p->m_pLeft = y;
    }
    else
    {
        m_pRoot = y;
    }

    //third step:make link between x and y
    y->m_pLeft = x;
    x->m_pParent = y;
}

void RbTree::m_fRightRotate(RbTreeNode *node)
{
    /* 
		 * right rotate by node y
		 *        p                   p 
		 *       /                   / 
		 *      y                   x 
		 *     / \                 / \ 
		 *    x  ry   ----->      lx  y 
		 *   / \                     / \ 
		 * lx  rx                   rx ry 

		 */

    RbTreeNode *y = node;         //must
    RbTreeNode *p = y->m_pParent; //may be
    RbTreeNode *x = y->m_pLeft;   //must
    RbTreeNode *lx = x->m_pLeft;  //may be
    RbTreeNode *rx = x->m_pRight; //may be
    RbTreeNode *ry = y->m_pRight; //may be

    //first step:make link between y and rx
    y->m_pLeft = rx;
    if (rx != nullptr)
        rx->m_pParent = y;

    //second step:make link between x and p
    x->m_pParent = p;
    if (p != nullptr)
    {
        if (y == p->m_pLeft)
            p->m_pLeft = x;
        else
            p->m_pRight = x;
    }
    else
    {
        m_pRoot = x;
    }

    //third step:remake link between x and y
    x->m_pRight = y;
    y->m_pParent = x;
}
