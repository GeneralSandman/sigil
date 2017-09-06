#include "dict.h"
#include <iostream>

bool hsetCommand(std::deque<std::string> &args)
{
    std::cout << "invoke hsetCommand()\n";
    if (args.size() != 3)
    {
        std::cout << "error" << std::endl;
        return false;
    }
    std::string dict = args[0];
    std::string key = args[1];
    std::string value = args[2];

    std::shared_ptr<Dict<std::string, std::string>> d = Server::getCurrDb()->findDict(dict);
    if (d != nullptr)
    {
        d->dictSet(key, value);
    }
    else
    {
        std::cout<<"can't find this dict"<<std::endl;
    }
}

bool hmsetCommand(std::deque<std::string> &args)
{
    std::cout << "invoke hmsetCommand()\n";
}

bool hgetCommand(std::deque<std::string> &args)
{
    std::cout << "invoke hgetCommand()\n";

    if (args.size() != 2)
    {
        std::cout << "error" << std::endl;
        return false;
    }
    std::string dict = args[0];
    std::string key = args[1];
    std::shared_ptr<Dict<std::string, std::string>> d = Server::getCurrDb()->findDict(dict);
    auto res = d->dictGet(key);
    std::cout << res << endl;
}
