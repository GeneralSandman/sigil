#include "../dict.h"
#include "../sigil.h"
#include "../command.h"
#include "../log.h"
#include "../list.h"
#include "../set.h"
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
    {
        initLogger("log/debug.log",
                   "log/info.log",
                   "log/warn.log",
                   "log/error.log",
                   "log/fatal.log",
                   Debug);
        {
            Server *server = Server::getServerInstace();
            server->load();
            //basic
            RegisterCommand("dbs", listDbsCommand);
            RegisterCommand("createdb", createDbCommand);
            RegisterCommand("deletedb", deleteDbCommand);
            RegisterCommand("select", selectCurrDbCommand);
            RegisterCommand("db", showCurrDbCommand);
            RegisterCommand("quit", quitCommand);
            RegisterCommand("save", saveCommand);

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
            RegisterCommand("hlen", hlenCommand);
            RegisterCommand("hclear", hclearCommand);

            // //set
            // RegisterCommand("sadd", saddCommand);
            // RegisterCommand("spop", spopCommand);
            // RegisterCommand("srem", sremCommand);
            // RegisterCommand("scard", scardCommand);
            // RegisterCommand("smem", smemCommand);
            // RegisterCommand("sismem", sismemCommand);
            // RegisterCommand("sinter", sinterCommand);
            // RegisterCommand("sunion", sunionCommand);
            // RegisterCommand("sdiff", sdiffCommand);

            welcome();
            Command com(server);
            while (server->runing())
            {
                com.waitCommand();
            }

            delete server;
        }
    }

    return 0;
}
