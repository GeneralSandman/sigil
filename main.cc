#include <iostream>
#include <deque>
#include <cstring>
#include <map>



bool selectDbCommand(std::deque<std::string> &arg)
{
    if(arg.size()!=1){
        std::cout<<"arg number is error\n";
        return false;
    }
    //set Server::m_nCurrDb to arg[0]

}

bool hsetCommand(std::deque<std::string> &arg)
{
    std::cout << "invoke hsetCommand\n";
    if (arg.size() != 3)
    {
        std::cout << "(error) ERR wrong number of arguments for 'hset' command\n";
        return false;
    }
    std::string hashname = arg[0];
    std::string key = arg[1];
    std::string value = arg[2];

    return true;
}

bool hgetCommand(std::deque<std::string> &arg)
{
    std::cout << "invoke hgetCommand\n";
    if (arg.size() != 2)
    {
        std::cout << "";
    }
}

bool linsertCommand(std::deque<std::string> &arg)
{
    std::cout << "invoke linsertCommand\n";
}

void parseCommand(std::deque<std::string> &res, char *com)
{
    int length = strlen(com);
    std::string tmp;

    for (int i = 0; i < length; i++)
    {
        if (com[i] != ' ')
        {
            tmp += com[i];
        }
        else
        {
            if (!tmp.empty())
                res.push_back(tmp);
            tmp = "";
        }
    }
    if (!tmp.empty())
        res.push_back(tmp);
}

void invokeCommand(std::deque<std::string> &res)
{
    std::string command = res.front();
    res.pop_front();
    auto p = string2command.find(command);
    if (p == string2command.end() || p->second == nullptr)
    {
        std::cout << "command error:" << command << "\n";
    }
    else
    {
        p->second(res);
    }
}
int getCommand()
{
    char com[256];
    std::cin.getline(com, 20, '\n');

    std::deque<std::string> res;

    parseCommand(res, com);
    invokeCommand(res);
    // for (auto t : res)
    // std::cout << t << std::endl;
}

int main()
{
    string2command["select"] = selectDbCommand;
    string2command["hset"] = hsetCommand;
    string2command["linsert"] = linsertCommand;

    std::cout << "sigil version 1.0\n";
    while (1)
    {
        std::cout << "sigil>:";
        getCommand();
    }
    return 0;
}