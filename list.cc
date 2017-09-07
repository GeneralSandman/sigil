#include "list.h"
#include "sigil.h"
#include <deque>
#include <string>

bool lmemCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lmem)" << std::endl;
}

bool lpushCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lpush)" << std::endl;
    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    for (auto t : args)
        p_list->add_head(t);
}

bool rpushCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (rpush)" << std::endl;
    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    for (auto t : args)
        p_list->add_tail(t);
}

bool lpopCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lpop)" << std::endl;
    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    p_list->pop_head();
}

bool rpopCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (rpop)" << std::endl;
    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    p_list->pop_tail();
}

bool llenCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (llen)" << std::endl;
    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    std::cout << "length:" << p_list->m_nLen << std::endl;
}

bool lindexCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lindex)" << std::endl;
    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    //not finish
}

bool linsertCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (linsert)" << std::endl;
    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    //not finish
}

bool lrangeCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lrange)" << std::endl;
    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    //not finish
}

bool lremCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lrem)" << std::endl;
    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    std::cout << "remove:" << std::endl;
    for (auto t : args)
    {
        p_list->dele(t);
        std::cout << t << std::endl;
    }
}

bool lclearCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lclear)" << std::endl;
    std::string list = args.front();
    args.pop_front();
    shared_of_list p_list = Server::getCurrDb()->findList(list);
    std::cout << p_list->m_nLen << std::endl;
    p_list->clear();
}
