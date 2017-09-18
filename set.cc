#include "set.h"
#include "log.h"

bool saddCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (sadd)" << std::endl;
}

bool spopCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (spop)" << std::endl;
}

bool sremCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (srem)" << std::endl;
}

bool scardCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (scard)" << std::endl;
}

bool smemCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (smem)" << std::endl;
}

bool sismemCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (sismem)" << std::endl;
}

bool sinterCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (sinter)" << std::endl;
}

bool sunionCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (sunion)" << std::endl;
}

bool sdiffCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (sdiff)" << std::endl;
}