#include "../list.h"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

int main()
{

    {
        List<string> l("test");

        for (int i = 0; i < 8; i++)
        {
            l.add_head("a");
        }

        ListIter<string> iter(&l, AL_START_HEAD);        
        ListNode<string> *t = nullptr;
        while (t = iter.getListNext())
        {
            std::cout << t->m_nValue << std::endl;
        }
    }

    return 0;
}