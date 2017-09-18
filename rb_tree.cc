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

void RbTree::m_fFixAfterInsert(RbTreeNode *node)
{
    RbTreeNode *parent = nullptr, *gparent = nullptr;

    while ((parent = node->getParent()) != nullptr && parent->getColor() == red)
    {
        gparent = node->getGParent();

        if (parent == gparent->getLeft())
        {
            RbTreeNode *uncle = node->getUncle();

            if (uncle != nullptr && uncle->getColor() == red)
            {
                parent->setColor(black);
                uncle->setColor(black);
                gparent->setColor(red);
                node = gparent;
                continue;
            }

            if (node == parent->getRight())
            { //uncle is black && node is parent's right-node
                m_fLeftRotate(parent);
                RbTreeNode *tmp = parent;
                parent = node;
                node = tmp;
            }

            parent->setColor(black);
            gparent->setColor(red);
            m_fRightRotate(gparent);
        }
        else
        {
            RbTreeNode *uncle = node->getUncle();

            if (uncle != nullptr && uncle->getColor() == red)
            {
                parent->setColor(black);
                uncle->setColor(black);
                gparent->setColor(red);
                node = gparent;
                continue;
            }

            if (node == parent->getLeft())
            {
                m_fRightRotate(parent);
                RbTreeNode *tmp = parent;
                parent = node;
                node = tmp;
            }

            parent->setColor(black);
            gparent->setColor(red);
            m_fLeftRotate(gparent);
        }
    }

    m_pRoot->setColor(black);
}

void RbTree::m_fInsertNode(const int &value, RbTreeNode *node)
{
    RbTreeNode *pre = node, *insert = node;
    while (insert != nullptr)
    {
        pre = insert;

        if (value < insert->getValue())
            insert = insert->getLeft();
        else if (value > insert->getValue())
            insert = insert->getRight();
    }

    RbTreeNode *newnode = new RbTreeNode(value);
    newnode->setParent(pre);
    if (value < pre->getValue())
        pre->setLeft(newnode);
    else if (value > pre->getValue())
        pre->setRight(newnode);

    m_fFixAfterInsert(newnode);
}

void RbTree::m_fFixAfterDelete(RbTreeNode *, RbTreeNode *)
{
    RBNode<T> other;

    while ((node == null || isBlack(node)) && (node != this.root))
    {
        if (parent.left == node)
        {                         //node是左子节点，下面else与这里的刚好相反
            other = parent.right; //node的兄弟节点
            if (isRed(other))
            { //case1: node的兄弟节点other是红色的
                setBlack(other);
                setRed(parent);
                leftRotate(parent);
                other = parent.right;
            }

            //case2: node的兄弟节点other是黑色的，且other的两个子节点也都是黑色的
            if ((other.left == null || isBlack(other.left)) &&
                (other.right == null || isBlack(other.right)))
            {
                setRed(other);
                node = parent;
                parent = parentOf(node);
            }
            else
            {
                //case3: node的兄弟节点other是黑色的，且other的左子节点是红色，右子节点是黑色
                if (other.right == null || isBlack(other.right))
                {
                    setBlack(other.left);
                    setRed(other);
                    rightRotate(other);
                    other = parent.right;
                }

                //case4: node的兄弟节点other是黑色的，且other的右子节点是红色，左子节点任意颜色
                setColor(other, colorOf(parent));
                setBlack(parent);
                setBlack(other.right);
                leftRotate(parent);
                node = this.root;
                break;
            }
        }
        else
        { //与上面的对称
            other = parent.left;

            if (isRed(other))
            {
                // Case 1: node的兄弟other是红色的
                setBlack(other);
                setRed(parent);
                rightRotate(parent);
                other = parent.left;
            }

            if ((other.left == null || isBlack(other.left)) &&
                (other.right == null || isBlack(other.right)))
            {
                // Case 2: node的兄弟other是黑色，且other的俩个子节点都是黑色的
                setRed(other);
                node = parent;
                parent = parentOf(node);
            }
            else
            {

                if (other.left == null || isBlack(other.left))
                {
                    // Case 3: node的兄弟other是黑色的，并且other的左子节点是红色，右子节点为黑色。
                    setBlack(other.right);
                    setRed(other);
                    leftRotate(other);
                    other = parent.left;
                }

                // Case 4: node的兄弟other是黑色的；并且other的左子节点是红色的，右子节点任意颜色
                setColor(other, colorOf(parent));
                setBlack(parent);
                setBlack(other.left);
                rightRotate(parent);
                node = this.root;
                break;
            }
        }
    }
    if (node != null)
        setBlack(node);
}

void RbTree::m_fDeleteNode(RbTreeNode *node)
{
    RBNode<T> child, parent;
    boolean color;

    //1. 被删除的节点“左右子节点都不为空”的情况
    if ((node.left != null) && (node.right != null))
    {
        //先找到被删除节点的后继节点，用它来取代被删除节点的位置
        RBNode<T> replace = node;
        //  1). 获取后继节点
        replace = replace.right;
        while (replace.left != null)
            replace = replace.left;

        //  2). 处理“后继节点”和“被删除节点的父节点”之间的关系
        if (parentOf(node) != null)
        { //要删除的节点不是根节点
            if (node == parentOf(node).left)
                parentOf(node).left = replace;
            else
                parentOf(node).right = replace;
        }
        else
        { //否则
            this.root = replace;
        }

        //  3). 处理“后继节点的子节点”和“被删除节点的子节点”之间的关系
        child = replace.right; //后继节点肯定不存在左子节点！
        parent = parentOf(replace);
        color = colorOf(replace); //保存后继节点的颜色
        if (parent == node)
        { //后继节点是被删除节点的子节点
            parent = replace;
        }
        else
        { //否则
            if (child != null)
                setParent(child, parent);
            parent.left = child;
            replace.right = node.right;
            setParent(node.right, replace);
        }
        replace.parent = node.parent;
        replace.color = node.color; //保持原来位置的颜色
        replace.left = node.left;
        node.left.parent = replace;

        if (color == BLACK)
        {                               //4. 如果移走的后继节点颜色是黑色，重新修整红黑树
            removeFixUp(child, parent); //将后继节点的child和parent传进去
        }
        node = null;
        return;
    }
}

RbTreeNode *RbTree::m_fFindLeftSubTreeMaxNode(RbTreeNode *node)
{
    RbTreeNode *leftmax = nullptr, *left = node->getLeft();
    while (left)
    {
        leftmax = left;
        left = left->getRight();
    }
    return leftmax;
}

RbTreeNode *RbTree::m_fFindRightSubTreeMinNode(RbTreeNode *node)
{
    RbTreeNode *rightmin = nullptr, *right = node->getRight();
    while (right != nullptr)
    {
        rightmin = right;
        right = right->getLeft();
    }
    return rightmin;
}

void RbTree::m_fPreorder(RbTreeNode *node)
{
    if (node)
    {
        cout << node->getValue() << " ";
        m_fPreorder(node->getLeft());
        m_fPreorder(node->getRight());
    }
}

void RbTree::m_fInorder(RbTreeNode *node)
{
    if (node)
    {
        m_fInorder(node->getLeft());
        cout << node->getValue() << " ";
        m_fInorder(node->getRight());
    }
}

void RbTree::m_fPostorder(RbTreeNode *node)
{
    if (node)
    {
        m_fPostorder(node->getLeft());
        m_fPostorder(node->getRight());
        cout << node->getValue() << " ";
    }
}

void RbTree::m_fLevel(vector<vector<int>> &result, RbTreeNode *node, int level)
{
    if (node == nullptr)
        return;
    if (level == result.size())
        result.push_back(vector<int>());
    result[level].push_back(node->getValue());
    m_fLevel(result, node->getLeft(), level + 1);
    m_fLevel(result, node->getRight(), level + 1);
}

void RbTree::m_fDisplay(vector<string> &result, RbTreeNode *node, int level)
{
    if (node != nullptr)
    {
        string tmp;

        for (int i = 0; i < level - 1; i++)
            tmp += "      ";
        if (level)
            tmp += "+-----";
        tmp += std::to_string(node->getValue());

        result.push_back(tmp);
        m_fDisplay(result, node->getLeft(), level + 1);
        string t;
        for (int i = 0; i < level; i++)
            t += "      ";
        t += '|';
        result.push_back(t);
        result.push_back(t);
        m_fDisplay(result, node->getRight(), level + 1);
    }
}

void RbTree::m_fDeleteAllNode(RbTreeNode *node, int &deleteNumber)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->getLeft() != nullptr)
        m_fDeleteAllNode(node->getLeft(), deleteNumber);
    if (node->getRight() != nullptr)
        m_fDeleteAllNode(node->getRight(), deleteNumber);
    if (node->getLeft() == nullptr && node->getRight() == nullptr)
    {
        RbTreeNode *parent = node->getParent();
        if (parent != nullptr)
        {
            if (node->getValue() < parent->getValue())
                parent->setLeft(nullptr);
            else
                parent->setRight(nullptr);
        }

        node->setParent(nullptr);
        deleteNumber++;
        m_nNumber--;
        delete node;
    }
}

int RbTree::m_fGetHeight(RbTreeNode *node)
{
    if (node == nullptr)
        return 0;
    return max(m_fGetHeight(node->getLeft()), m_fGetHeight(node->getRight())) + 1;
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

bool RbTree::FindNode(const int &value)
{
    RbTreeNode *node = m_fFindNode(value);
    if (node != nullptr)
        return true;
    else
        return false;
}

void RbTree::PrintTreePreorder()
{
    cout << "preorder: ";
    m_fPreorder(m_pRoot);
    cout << endl;
}

void RbTree::PrintTreeInorder()
{
    cout << "inorder: ";
    m_fInorder(m_pRoot);
    cout << endl;
}

void RbTree::PrintTreePostorder()
{
    cout << "postorder: ";
    m_fPostorder(m_pRoot);
    cout << endl;
}

void RbTree::PrintTreeLevel()
{
    vector<vector<int>> result;
    m_fLevel(result, m_pRoot, 0);
    if (result.empty())
        cout << "empty\n";
    for (int i = 0; i < result.size(); i++)
    {
        cout << "level " << i + 1 << ":";
        for (auto t : result[i])
            cout << t << " ";
        cout << endl;
    }
}

void RbTree::DisplayTree()
{
    vector<string> result;
    m_fDisplay(result, m_pRoot, 0);
    for (auto t : result)
        cout << t << endl;
}

void RbTree::InsertNode(const int &value)
{
    if (m_pRoot == nullptr)
    {
        m_pRoot = new RbTreeNode(value);
    }
    else
    {
        m_fInsertNode(value, m_pRoot);
    }
    m_nNumber++;
}

void RbTree::DeleteNode(const int &value)
{
    RbTreeNode *DeleteNode = m_fFindNode(value);

    if (DeleteNode != nullptr)
    {
        m_fDeleteNode(DeleteNode);
        m_nNumber--;
    }
    else
    {
        cout << "don't exists this value\n";
    }
}

int RbTree::getNumber(void)
{
    return m_nNumber;
}

bool RbTree::testBalance(void)
{
    int balace = abs(m_fGetHeight(m_pRoot->getLeft()) - m_fGetHeight(m_pRoot->getRight()));
    if (balace > 1)
        return false;
    else
        return true;
}

void RbTree::testRoat(void)
{
    RbTreeNode *node = m_fFindNode(10);
    m_fRoatLeftRight(node);
}
void RbTree::m_fLeftRotate(RbTreeNode *node)
{
    /* 
		 * 左旋示意图：对节点x进行左旋 
		 *     p                       p 
		 *    /                       / 
		 *   x                       y 
		 *  / \                     / \ 
		 * lx  y      ----->       x  ry 
		 *    / \                 / \ 
		 *   ly ry               lx ly 
		 */
    RbTreeNode *x = node;
    RbTreeNode *p = x->getParent();
    RbTreeNode *lx = x->getLeft();
    RbTreeNode *y = x->getRight();
    RbTreeNode *ly = y->getLeft();
    RbTreeNode *ry = y->getRight();

    x->setRight(ly);
    if (ly)
        ly->setParent(x);

    y->setParent(p);
    if (p)
    {
        if (x == p->getLeft())
            p->setLeft(y);
        else
            p->setRight(y);
    }
    else
    {
        m_pRoot = y;
    }

    y->setLeft(x);
    x->setParent(y);
}
void RbTree::m_fRightRotate(RbTreeNode *node)
{
    /* 
		 * 左旋示意图：对节点y进行右旋 
		 *        p                   p 
		 *       /                   / 
		 *      y                   x 
		 *     / \                 / \ 
		 *    x  ry   ----->      lx  y 
		 *   / \                     / \ 
		 * lx  rx                   rx ry 

		 */

    RbTreeNode *y = node;
    RbTreeNode *p = y->getParent();
    RbTreeNode *x = y->getLeft();
    RbTreeNode *lx = x->getLeft();
    RbTreeNode *rx = x->getRight();
    RbTreeNode *ry = y->getRight();

    y->setLeft(rx);
    if (rx)
        rx->setParent(y);

    x->setParent(p);
    if (p)
    {
        if (y == p->getLeft())
            p->setLeft(x);
        else
            p->setRight(x);
    }
    else
    {
        m_pRoot = x;
    }

    x->setRight(y);
    y->setParent(x);
}

void RbTree::m_fRoatLeftLeft(RbTreeNode *node)
{
    /*
            x            y
           / \         /    \
          y   q       z     x
         /           /        \
        z           w           q
       /
       w
      
      */

    m_fRightRotate(node);
}
void RbTree::m_fRoatLeftRight(RbTreeNode *node)
{
    m_fLeftRotate(node->getLeft());
    // PrintTreeLevel();

    m_fRightRotate(node);
}
void RbTree::m_fRoatRightLeft(RbTreeNode *node)
{
    m_fRightRotate(node->getRight());
    m_fLeftRotate(node);
}
void RbTree::m_fRoatRightRight(RbTreeNode *node)
{
    m_fLeftRotate(node);
}
