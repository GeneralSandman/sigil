#include "list.h"
#include "api.h"
#include "sigil.h"
#include <deque>
#include <string>

bool lmemCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lmem)" << std::endl;

    if (args.size() != 1)
    {
        handleArgsError();
        return false;
    }
    std::string list = args[0];
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    if (p_list == nullptr)
    {
        std::cout << "(error) no list \"" << list << "\"" << std::endl;
        return false;
    }

    std::vector<std::string> res;
    if (p_list->getAll(res))
    {
        std::cout << "length: " << res.size() << std::endl;
        for (int i = 0; i < res.size(); i++)
            std::cout << i << ") " << res[i] << std::endl;
        return true;
    }
}

bool lpushCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lpush)" << std::endl;

    if (args.size() < 2)
    {
        handleArgsError();
        return false;
    }

    std::string list = args.front();
    args.pop_front();

    int num = 0;

    shared_of_list p_list = Server::getCurrDb()->getList(list);
    for (auto t : args)
    {
        if (p_list->add_head(t))
        {
            num++;
        }
    }
    std::cout << num << std::endl;
}

bool rpushCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (rpush)" << std::endl;

    if (args.size() < 2)
    {
        handleArgsError();
        return false;
    }

    std::string list = args.front();
    args.pop_front();

    int num = 0;

    shared_of_list p_list = Server::getCurrDb()->getList(list);

    for (auto t : args)
    {
        if (p_list->add_tail(t))
        {
            num++;
        }
    }
    std::cout << num << std::endl;
}

bool lpopCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lpop)" << std::endl;

    if (args.size() != 1)
    {
        handleArgsError();
        return false;
    }

    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    if (p_list == nullptr)
    {
        std::cout << "(error) no list \"" << list << "\"" << std::endl;
        return false;
    }

    std::cout << p_list->pop_head() << std::endl;
    return true;
}

bool rpopCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (rpop)" << std::endl;

    if (args.size() != 1)
    {
        handleArgsError();
        return false;
    }

    std::string list = args[0];
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    if (p_list == nullptr)
    {
        std::cout << "(error) no list \"" << list << "\"" << std::endl;
        return false;
    }
    std::cout << p_list->pop_tail() << std::endl;
    return true;
}

bool llenCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (llen)" << std::endl;

    if (args.size() != 1)
    {
        handleArgsError();
        return false;
    }

    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    if (p_list == nullptr)
    {
        std::cout << "(error) no list \"" << list << "\"" << std::endl;
        return false;
    }

    std::cout << "length:" << p_list->m_nLen << std::endl;
    return true;
}

bool lindexCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lindex)" << std::endl;

    if (args.size() < 2 || args.size() > 3)
    {
        handleArgsError();
        return false;
    }

    std::string list = args[0];
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    if (p_list == nullptr)
    {
        std::cout << "(error) no list \"" << list << "\"" << std::endl;
        return false;
    }

    if (args.size() == 2)
    { //get value
        int index = atoi(args[1].c_str());
        std::string value;
        if (p_list->getByIndex(index, value))
        {
            std::cout << index << ") " << value << std::endl;
            return true;
        }
    }
    else if (args.size() == 3)
    {
        int index = atoi(args[1].c_str());
        std::string value = args[2];
        if (p_list->setByIndex(index, value))
        {
            std::cout << index << ") " << value << std::endl;
            return true;
        }
    }
}

bool linsertCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (linsert)" << std::endl;
    if (args.size() != 4)
    {
        handleArgsError();
        return false;
    }

    std::string list = args[0];

    shared_of_list p_list = Server::getCurrDb()->findList(list);
    if (p_list == nullptr)
    {
        std::cout << "(error) no list \"" << list << "\"" << std::endl;
        return false;
    }

    std::string flag = args[1];
    std::string pre = args[2];
    std::string newv = args[3];

    if (flag == "before")
    {
        if (p_list->insert(newv, pre, Before))
            return true;
    }
    else if (flag == "after")
    {
        if (p_list->insert(newv, pre, After))
            return true;
    }
}

bool lrangeCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lrange)" << std::endl;

    if (args.size() != 3)
    {
        handleArgsError();
        return false;
    }

    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    //not finish

    if (p_list == nullptr)
    {
        std::cout << "(error) no list \"" << list << "\"" << std::endl;
        return false;
    }

    int begin = atoi(args[0].c_str());
    int end = atoi(args[1].c_str());

    std::vector<std::string> res;
    if (p_list->getByRange(res, begin, end))
    {
        for (int i = 0, index = begin; i < res.size(); i++, index++)
            std::cout << index << ") " << res[i] << std::endl;
        return true;
    }
}

bool lremCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lrem)" << std::endl;
    if (args.size() != 2)
    {
        handleArgsError();
        return false;
    }
    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);

    if (p_list == nullptr)
    {
        std::cout << "(error) no list \"" << list << "\"" << std::endl;
        return false;
    }
    else
    {
        for (auto t : args)
        {
            if (p_list->dele(t))
                std::cout << t << std::endl;
        }
        return true;
    }
}

bool lclearCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lclear)" << std::endl;
    if (args.size() != 1)
    {
        handleArgsError();
        return false;
    }

    std::string list = args[0];
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    if (p_list == nullptr)
    {
        std::cout << "(error) no list \"" << list << "\"" << std::endl;
        return false;
    }
    else
    {
        p_list->clear();
        return true;
    }
}
