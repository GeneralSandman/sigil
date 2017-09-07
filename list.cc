#include "list.h"
#include <deque>
#include <string>
namespace list
{
}

bool lpushCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lpush)" << std::endl;
}

bool rpushCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (rpush)" << std::endl;
}

bool lpopCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lpop)" << std::endl;
}

bool rpopCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (rpop)" << std::endl;
}

bool llenCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (llen)" << std::endl;
}

bool lindexCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lindex)" << std::endl;
}

bool linsertCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (linsert)" << std::endl;
}

bool lrangeCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lrange)" << std::endl;
}

bool lremCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lrem)" << std::endl;
}

bool lclearCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (lclear)" << std::endl;
}
