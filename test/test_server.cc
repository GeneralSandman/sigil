#include "../dict.h"
#include "../sigil.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void welcome()
{
    // std::cout << "sigil version 1.1\n";
    ifstream f;
    f.open("icon.txt", std::ios_base::in);
    std::string result;
    while (getline(f, result, '\n'))
        cout << result << endl;
}
int main()
{
    Server *server = Server::getServerInstace();
    Server::regitCommand("hset", hsetCommand);
    Server::regitCommand("hmset", hmsetCommand);
    Server::regitCommand("hget", hgetCommand);
    Server::regitCommand("dbs", listDbsCommand);
    Server::regitCommand("createdb", createDbCommand);
    // Server::regitCommand("deletedb", deleteDbCommand);
    Server::regitCommand("select", selectCurrDbCommand);
    Server::regitCommand("db", showCurrDbCommand);

    Command com(server);

    welcome();

    while (1)
    {
        std::cout << "sigil>:";
        com.waitCommand();
    }

    return 0;
}
