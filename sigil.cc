#include "sigil.h"
#include "log.h"
#include "persist.h"
#include <iostream>

int Db::m_nDbsNum = 0;
int Db::m_nCreatedDbs = 0;
Server *Server::m_pServerInstance = nullptr;
std::string Server::m_nDbFile = "/home/li/sigil/test/dbfile/sigil.db";
std::shared_ptr<Db> Server::m_nCurrDb = nullptr;
std::map<std::string, command> Server::m_nCommand;

Db::Db(const std::string &name)
    : m_nName(name)
{
    m_nNumber = m_nCreatedDbs;
    m_nDbsNum++;
    m_nCreatedDbs++;
    LOG(Debug) << "class Db constructor" << std::endl;
}

//If dict exists,return shared_ptr<Dict>
//else,return nullptr
shared_of_dict Db::findDict(const std::string &dict)
{
    auto p = m_nDicts.find(dict);
    if (p == m_nDicts.end()) //create new dict
        return nullptr;
    else
        return p->second;
}

//If dict exists,return shared_ptr<Dict>
//else,create new dict and return
shared_of_dict Db::getDict(const std::string &dict)
{
    auto p = m_nDicts.find(dict);
    if (p == m_nDicts.end()) //create new dict
    {
        std::shared_ptr<Dict<std::string, std::string>> newdict =
            std::make_shared<Dict<std::string, std::string>>(dict);
        m_nDicts[dict] = newdict;
        return newdict;
    }
    else
        return p->second;
}

//If list exists,return shared_ptr<List>
//else,return nullptr
shared_of_list Db::findList(const std::string &list)
{
    auto p = m_nLists.find(list);
    if (p == m_nLists.end()) //create new list
    {
        return nullptr;
    }
    else
        return p->second;
}

//If list exists,return shared_ptr<List>
//else,create new list and return
shared_of_list Db::getList(const std::string &list)
{
    auto p = m_nLists.find(list);
    if (p == m_nLists.end()) //create new list
    {
        shared_of_list newlist =
            std::make_shared<List<std::string>>(list);
        m_nLists[list] = newlist;
        return newlist;
    }
    else
        return p->second;
}

Db::~Db()
{
    for (auto t : m_nDicts)
        t.second = nullptr;
    for (auto t : m_nLists)
        t.second = nullptr;
    m_nDbsNum--;

    LOG(Debug) << "class Db destructor" << std::endl;
}

////server api

Server::Server()
{
    m_pPersist = std::make_shared<Persist>(m_nDbFile);
    m_nRun = true;

    LOG(Debug) << "class Server constructor\n";
}

void Server::check()
{
    //check if have init datebase
    if (getDbsNum() == 0)
    {
        createDb("init");
    }
    selectCurrDb("init");
}

void Server::listDbs(void)
{
    std::cout << Db::m_nDbsNum << ":" << std::endl;
    for (auto t : m_nDbs)
        std::cout << t.second->getNumber() << "):" << t.first << std::endl;
}

bool Server::createDb(const std::string &db)
{
    auto p = m_nDbs.find(db);
    if (p != m_nDbs.end())
    {
        std::cout << "(error) " << db << "existed,can't create\n";
        return false;
    }
    std::shared_ptr<Db> newdb = std::make_shared<Db>(db);
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
        m_nDbs.erase(p);
    }
    else
    {
        std::cout << "(error) can't delete " << db << std::endl;
    }
}

bool Server::selectCurrDb(const std::string &db)
{
    auto p = m_nDbs.find(db);
    if (p != m_nDbs.end())
    {
        m_nCurrDb = p->second;
        std::cout << "select db (" << db << ")" << std::endl;
    }
    else
    {
        std::cout << "(error) can't select (" << db << ")" << std::endl;
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
        std::cout << "(error) " << db << " not exists\n";
        return;
    }
    m_nCurrDb = p->second;
}

command Server::findCommand(const std::string &n)
{
    auto p = m_nCommand.find(n);
    if (p == m_nCommand.end())
    {
        return nullptr;
    }
    return p->second;
}

bool Server::save()
{
    m_pPersist->save();
}

bool Server::bgsave()
{
    m_pPersist->bgsave();
}

bool Server::load()
{
    m_pPersist->load();
    check();//check have init database
}

Server::~Server()
{
    m_pPersist = nullptr;
    for (auto t : m_nDbs)
    {
        t.second = nullptr;
    }
    LOG(Debug) << "class Server destructor\n";
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
        std::cout << "(error) not command \"" << m_nName << "\"\n";
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
    if (args.empty())
    {
        std::cout << "(error) args error\n";
        return false;
    }
    for (auto t : args)
    {
        Server::getServerInstace()->createDb(t);
    }
    return true;
}

bool deleteDbCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (deletedb)" << std::endl;
    if (args.empty())
    {
        std::cout << "(error) args error\n";
        return false;
    }
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
        std::cout << "(error) args error" << std::endl;
        return false;
    }
    return Server::getServerInstace()->selectCurrDb(args[0]);
}

bool showCurrDbCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (db)" << std::endl;

    if (!args.empty())
    {
        std::cout << "(error) args error" << std::endl;
        return false;
    }
    Server::getServerInstace()->showCurrDb();
}

bool quitCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (quit)" << std::endl;
    if (!args.empty())
    {
        std::cout << "(error) args error" << std::endl;
        return false;
    }
    Server::getServerInstace()->stop();
    Server::getServerInstace()->save();
}

bool saveCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (save)" << std::endl;
    if (!args.empty())
    {
        std::cout << "(error) args error" << std::endl;
        return false;
    }
    Server::getServerInstace()->save();
}

bool bgsaveCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (dgsave)" << std::endl;
    if (!args.empty())
    {
        std::cout << "(error) args error" << std::endl;
        return false;
    }
    Server::getServerInstace()->bgsave();
}
