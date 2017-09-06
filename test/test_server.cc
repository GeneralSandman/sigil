#include "../dict.h"
#include "../sigil.h"
#include "../log.h"
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
    initLogger("info.log", "warn.log", "error.log");

    Server *server = Server::getServerInstace();

    RegisterCommand("dbs", listDbsCommand);
    RegisterCommand("createdb", createDbCommand);
    RegisterCommand("deletedb", deleteDbCommand);
    RegisterCommand("select", selectCurrDbCommand);
    RegisterCommand("db", showCurrDbCommand);

    RegisterCommand("hset", hsetCommand);
    RegisterCommand("hmset", hmsetCommand);
    RegisterCommand("hget", hgetCommand);

    welcome();
    Command com(server);
    while (1)
    {
        std::cout << "sigil>:";
        com.waitCommand();
    }

    delete Logger::getLoggerInstance();

    return 0;
}
