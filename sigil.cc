#include "sigil.h"
#include "command.h"
#include <iostream>

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
