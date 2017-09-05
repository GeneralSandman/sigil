#include "../dict.h"
#include "../sigil.h"
#include "../command.h"
#include <iostream>
#include <string>

using namespace std;
int main()
{
    shared_ptr<Server> server;
    server->regitCommand("select", );
    server->regitCommand("hset", );
    server->regitCommand("hget", );

    server->regitCommand("linsert", );

    Command com(server);
    while (1)
    {
        com.waitCommand();
    }

    return 0;
}
