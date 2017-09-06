#include "sigil.h"
#include <iostream>

Server *Server::serverInstance = nullptr;
std::shared_ptr<Db> Server::m_nCurrDb = nullptr;
std::map<std::string, command> Server::m_nCommand;

Db::Db(const std::string &name) : m_nName(name)
{
    std::cout << "class Db construct\n";
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
    std::cout << "class Db destory\n";
}

////server api

Server::Server()
{
    createDb("init");
    selectCurrDb("init");

    std::cout << "class server constuct\n";
}

void Server::listDbs(void)
{
    for (auto t : m_nDbs)
        std::cout << t.first << endl;
}

bool Server::createDb(const std::string &db)
{
    std::shared_ptr<Db> newdb = make_shared<Db>(db);
    m_nDbs[db] = newdb;
}

bool Server::deleteDb(const std::string &db)
{
    auto p = m_nDbs.find(db);
    if (p != m_nDbs.end())
    {
        p->second = nullptr;
    }
    else
    {
        std::cout << "can't delete (" << db << ")" << endl;
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
    std::cout << "class Server destory\n";
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
    std::cout << "invoke listDbsCommand\n";
    Server::getServerInstace()->listDbs();
}
bool createDbCommand(std::deque<std::string> &args)
{
    std::cout << "invoke createDbCommand\n";
    for (auto t : args)
    {
        Server::getServerInstace()->createDb(t);
    }
}
bool deleteDbCommand(std::deque<std::string> &args)
{
    std::cout << "invoke deleteDbCommand\n";
    for (auto t : args)
    {
        Server::getServerInstace()->deleteDb(t);
    }
}
bool selectCurrDbCommand(std::deque<std::string> &args)
{
    std::cout << "invoke selectCurrDbCommand\n";
    if (args.size() != 1)
    {
        std::cout << "error" << std::endl;
        return false;
    }
    return Server::getServerInstace()->selectCurrDb(args[0]);
}
bool showCurrDbCommand(std::deque<std::string> &args)
{
    std::cout << "invoke showCurrDbCommand\n";
    if (args.size() != 0)
    {
        std::cout << "error" << std::endl;
        return false;
    }
    Server::getServerInstace()->showCurrDb();
}