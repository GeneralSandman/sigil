#include "../rbtree.h"

using namespace std;

int main()
{

    {
        RbTree tree;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
            tree.insert(i);
        tree.PrintTreeLevel();
    }

    return 0;
}