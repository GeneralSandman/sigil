#include "../list.h"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

int main()
{

    {
        List<string> l;
        for (int i = 0; i < 8; i++)
        {
            l.add_head("a");
        }

        for (int i = 0; i < 8; i++)
            cout << l.pop_tail();
    }

    {
        List<string> l;
        for (int i = 0; i < 8; i++)
        {
            l.add_head("a");
        }

        for (int i = 0; i < 8; i++)
            cout << l.pop_head();
    }
    return 0;
}