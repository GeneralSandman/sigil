#include "dict.h"
#include "sigil.h"
#include "log.h"
#include <iostream>

bool hsetCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (hset)" << std::endl;
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
        std::cout << "can't find this dict" << std::endl;
    }
}

bool hmsetCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (hmset)" << std::endl;
}

bool hgetCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (hget)" << std::endl;

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

bool hmgetCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (hmget)" << std::endl;
}

bool hlenCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (hlen)" << std::endl;
    // std::shared_ptr<Dict<std::string, std::string>> d = Server::getCurrDb()->findDict(dict);

}

///
// Server::regitCommand("hset", hsetCommand);
// Server::regitCommand("hmset", hmsetCommand);
// Server::regitCommand("hget", hgetCommand);

///