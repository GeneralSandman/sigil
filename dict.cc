#include "dict.h"
#include "sigil.h"
#include "log.h"
#include <iostream>

bool hsetCommand(std::deque<std::string> &args)
{
    LOG(Debug) << std::endl;
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
    //find the dict or create a new
    return d->dictSet(key, value);
}

bool hmsetCommand(std::deque<std::string> &args)
{
    LOG(Debug) << std::endl;
    LOG(Info) << "command (hmset)" << std::endl;

    if (args.size() % 2 == 0)
    {
        std::cout << "error" << std::endl;
        return false;
    }
    std::string dict = args.front();
    args.pop_front();
    std::shared_ptr<Dict<std::string, std::string>> d = Server::getCurrDb()->findDict(dict);

    while (args.size())
    {
        std::string key = args.front();
        args.pop_front();

        std::string value = args.front();
        args.pop_front();

        d->dictSet(key, value);
    }

    return true;
}

bool hgetCommand(std::deque<std::string> &args)
{
    LOG(Debug) << std::endl;
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
    LOG(Debug) << std::endl;
    LOG(Info) << "command (hmget)" << std::endl;

    if (args.size() <= 1)
    {
        std::cout << "error" << std::endl;
        return false;
    }

    std::string dict = args.front();
    args.pop_front();
    std::shared_ptr<Dict<std::string, std::string>> d = Server::getCurrDb()->findDict(dict);

    while (args.size())
    {
        std::string key = args.front();
        args.pop_front();

        auto res = d->dictGet(key);
        std::cout << key << ":" << res << endl;
    }
}

bool hlenCommand(std::deque<std::string> &args)
{
    LOG(Debug) << std::endl;
    LOG(Info) << "command (hlen)" << std::endl;

    // std::shared_ptr<Dict<std::string, std::string>> d = Server::getCurrDb()->findDict(dict);
    std::string dict = args[0];
    std::shared_ptr<Dict<std::string, std::string>> d = Server::getCurrDb()->findDict(dict);
    int length = d->dictLen();
    std::cout << "length:" << length << std::endl;
}

bool hclearCommand(std::deque<std::string> &args)
{
    LOG(Debug) << std::endl;
    LOG(Info) << "command (hclear)" << std::endl;

    std::string dict = args[0];
    std::shared_ptr<Dict<std::string, std::string>> d = Server::getCurrDb()->findDict(dict);
    d->dictClear();
}

///
// Server::regitCommand("hset", hsetCommand);
// Server::regitCommand("hmset", hmsetCommand);
// Server::regitCommand("hget", hgetCommand);

///