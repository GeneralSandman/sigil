#include "../list.h"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

int main()
{
    {
        list::List<string> l;
        for (int i = 0; i < 8; i++)
        {
            list::ListNode<string> *newnode =
                new list::ListNode<string>("a");
            l.addNodeHead(newnode);
            sleep(1.5);
        }
    }
    return 0;
}