#include "../dict.h"
#include "../sigil.h"
#include "../log.h"
#include "../list.h"
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

    //basic
    RegisterCommand("dbs", listDbsCommand);
    RegisterCommand("createdb", createDbCommand);
    RegisterCommand("deletedb", deleteDbCommand);
    RegisterCommand("select", selectCurrDbCommand);
    RegisterCommand("db", showCurrDbCommand);

    //list
    RegisterCommand("lmem", lmemCommand);
    RegisterCommand("lpush", lpushCommand);
    RegisterCommand("rpush", rpushCommand);
    RegisterCommand("lpop", lpopCommand);
    RegisterCommand("rpop", rpopCommand);
    RegisterCommand("llen", llenCommand);
    RegisterCommand("lindex", lindexCommand);
    RegisterCommand("linsert", linsertCommand);
    RegisterCommand("lrange", lrangeCommand);
    RegisterCommand("lrem", lremCommand);
    RegisterCommand("lclear", lclearCommand);

    //hash
    RegisterCommand("hset", hsetCommand);
    RegisterCommand("hmset", hmsetCommand);
    RegisterCommand("hget", hgetCommand);

    welcome();
    Command com(server);
    while (1)
    {
        std::cout << "sigil> ";
        com.waitCommand();
    }

    delete Logger::getLoggerInstance();

    return 0;
}
