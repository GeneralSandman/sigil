#include "../dict.h"
#include "../sigil.h"
#include "../command.h"
#include <iostream>
#include <string>

using namespace std;
int main()
{
    shared_ptr<Server> server = make_shared<Server>();
    Server::regitCommand("hset", hsetCommand);
    Server::regitCommand("hmset", hmsetCommand);
    Server::regitCommand("hget", hgetCommand);

    Command com(server);

    std::cout << "sigil version 1.1\n";
    while (1)
    {
        std::cout << "sigil>:";
        com.waitCommand();
    }

    return 0;
}
