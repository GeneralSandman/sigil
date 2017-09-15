#include "sigil.h"
#include "log.h"
#include "persist.h"
#include <iostream>

int Db::m_nDbsNum = 0;
Server *Server::m_pServerInstance = nullptr;
std::string Server::m_nDbFile = "/home/li/sigil/test/dbfile/sigil.db";
std::shared_ptr<Db> Server::m_nCurrDb = nullptr;
std::map<std::string, command> Server::m_nCommand;

Db::Db(const std::string &name)
    : m_nName(name)
{
    m_nNumber = m_nDbsNum;
    m_nDbsNum++;
    LOG(Debug) << "class Db construct" << std::endl;
}

std::string &Db::getName()
{
    return m_nName;
}

int Db::getNumber()
{
    return m_nNumber;
}

shared_of_dict Db::findDict(const std::string &dict)
{
    if (m_nPrevDict == dict)
        return m_pPrevDict;

    //have to find or create new dict
    m_nPrevDict = dict;
    auto p = m_nDicts.find(dict);
    if (p == m_nDicts.end()) //create new dict
    {
        std::shared_ptr<Dict<std::string, std::string>> newdict =
            make_shared<Dict<std::string, std::string>>(dict);
        m_nDicts[dict] = newdict;
        m_pPrevDict = newdict;
        LOG(Info) << "create new dict" << std::endl;
    }
    else
        m_pPrevDict = p->second;

    return m_pPrevDict;
}

shared_of_list Db::findList(const std::string &list)
{
    if (m_nPrevList == list)
        return m_pPrevList;

    //have to find or create new list
    m_nPrevList = list;
    auto p = m_nLists.find(list);
    if (p == m_nLists.end()) //create new list
    {
        shared_of_list newlist =
            make_shared<List<std::string>>(list);
        m_nLists[list] = newlist;
        m_pPrevList = newlist;
    }
    else
        m_pPrevList = p->second;
    return m_pPrevList;
}

Db::~Db()
{
    for (auto t : m_nDicts)
    {
        t.second = nullptr;
    }

    for (auto t : m_nLists)
    {
        t.second = nullptr;
    }

    LOG(Debug) << "class Db destory" << std::endl;
}

////server api

Server::Server()
{
    m_pPersist = make_shared<Persist>(m_nDbFile);
    m_nRun = true;
    createDb("init");
    selectCurrDb("init");

    m_pPersist->load();
    LOG(Debug) << "class Server construct\n";
}

void Server::listDbs(void)
{
    std::cout << Db::m_nDbsNum << ":" << std::endl;
    for (auto t : m_nDbs)
        std::cout << t.second->getNumber() << ":" << t.first << endl;
    // std::cout << t.first << endl;

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
}

Server::~Server()
{
    // if (m_pServerInstance)
    // {
    //     delete m_pServerInstance;
    //     m_pServerInstance = nullptr;
    // }
    for (auto t : m_nDbs)
    {
        t.second = nullptr;
    }
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

bool quitCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (quit)" << std::endl;
    Server::getServerInstace()->stop();
    Server::getServerInstace()->save();
}

bool saveCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (save)" << std::endl;
    Server::getServerInstace()->save();
}

bool bgsaveCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (dgsave)" << std::endl;
    Server::getServerInstace()->bgsave();
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