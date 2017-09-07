#include "sigil.h"
#include "log.h"
#include <iostream>

Server *Server::serverInstance = nullptr;
std::shared_ptr<Db> Server::m_nCurrDb = nullptr;
std::map<std::string, command> Server::m_nCommand;

Db::Db(const std::string &name) : m_nName(name)
{
    LOG(Info) << "create db(" << name << ")" << std::endl;
}

std::string &Db::getName()
{
    return m_nName;
}
std::shared_ptr<Dict<std::string, std::string>> Db::findDict(const std::string dict)
{
    auto p = m_nDicts.find(dict);
    if (p == m_nDicts.end())
    {
        std::shared_ptr<Dict<std::string, std::string>> newdict =
            make_shared<Dict<std::string, std::string>>(dict);
        m_nDicts[dict] = newdict;
        return newdict;
    }
    return p->second;
}
Db::~Db()
{
    LOG(Info) << "delete db(" << m_nName << ")" << std::endl;
}

////server api

Server::Server()
{
    createDb("init");
    selectCurrDb("init");

    LOG(Debug) << "class Server construct\n";
}

void Server::listDbs(void)
{
    std::cout << m_nDbs.size() << ":" << std::endl;
    for (auto t : m_nDbs)
        std::cout << t.first << endl;
    LOG(Info) << "list dbs" << std::endl;
}

bool Server::createDb(const std::string &db)
{
    std::shared_ptr<Db> newdb = make_shared<Db>(db);
    m_nDbs[db] = newdb;
    return true;
}

bool Server::deleteDb(const std::string &db)
{
    if (db == "init")
    {
        std::cout << "can't delete init db\n";
        return false;
    }
    auto p = m_nDbs.find(db);
    if (p != m_nDbs.end())
    {
        p->second = nullptr;
    }
    else
    {
        std::cout << "can't find " << db << endl;
    }
}

bool Server::selectCurrDb(const std::string &db)
{
    auto p = m_nDbs.find(db);
    if (p != m_nDbs.end())
    {
        m_nCurrDb = p->second;
    }
    else
    {
        std::cout << "can't select (" << db << ")" << endl;
    }
}
void Server::showCurrDb(void)
{
    std::cout << m_nCurrDb->getName() << std::endl;
}

void Server::setCurrDb(const std::string &db)
{
    auto p = m_nDbs.find(db);
    if (p == m_nDbs.end())
    {
        std::cout << db << " not exists\n";
        return;
    }
    m_nCurrDb = p->second;
}

command Server::findCommand(const std::string &n)
{
    auto p = m_nCommand.find(n);
    if (p == m_nCommand.end())
    {
        std::cout << "command error:" << n << "\n";
        return nullptr;
    }
    return p->second;
}
Server::~Server()
{
    LOG(Debug) << "class Server destory\n";
}
//////

////////command api
int Command::m_fGetCommand()
{
    std::cin.getline(m_nStr, 256, '\n');
}
void Command::m_fParseCommand()
{
    int length = strlen(m_nStr);
    std::string tmp;

    for (int i = 0; i < length; i++)
    {
        if (m_nStr[i] != ' ')
        {
            tmp += m_nStr[i];
        }
        else
        {
            if (!tmp.empty())
                m_nArgs.push_back(tmp);
            tmp = "";
        }
    }
    if (!tmp.empty())
        m_nArgs.push_back(tmp);

    m_nName = m_nArgs.front();
    m_nArgs.pop_front();
}
void Command::m_fInvokeCommand()
{
    auto com = m_pServer->findCommand(m_nName);
    if (com != nullptr)
    {
        com(m_nArgs);
    }
    else
    {
        std::cout << "command error:" << m_nName << "\n";
    }
}

//// XXXCommand function will be regist

bool listDbsCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (dbs)" << std::endl;

    Server::getServerInstace()->listDbs();
    return true;
}
bool createDbCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (createdb)" << std::endl;

    for (auto t : args)
    {
        Server::getServerInstace()->createDb(t);
    }
    return true;
}
bool deleteDbCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (deletedb)" << std::endl;

    for (auto t : args)
    {
        Server::getServerInstace()->deleteDb(t);
    }
    return true;
}
bool selectCurrDbCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (select)" << std::endl;

    if (args.size() != 1)
    {
        std::cout << "error" << std::endl;
        return false;
    }
    return Server::getServerInstace()->selectCurrDb(args[0]);
}
bool showCurrDbCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (db)" << std::endl;

    if (args.size() != 0)
    {
        std::cout << "error" << std::endl;
        return false;
    }
    Server::getServerInstace()->showCurrDb();
}

///

// RegisterCommand("dbs", listDbsCommand);
// RegisterCommand("createdb", createDbCommand);
// RegisterCommand("deletedb", deleteDbCommand);
// RegisterCommand("select", selectCurrDbCommand);
// RegisterCommand("db", showCurrDbCommand);
///

// Server::regitCommand("dbs", listDbsCommand);
// Server::regitCommand("createdb", createDbCommand);
// Server::regitCommand("deletedb", deleteDbCommand);
// Server::regitCommand("select", selectCurrDbCommand);
// Server::regitCommand("db", showCurrDbCommand);