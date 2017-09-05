#ifndef SIGIL_H
#define SIGIL_H
#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <deque>

typedef bool (*command)(std::deque<std::string> &);

class Dict;
class Db;
class Server
{
  private:
    std::map<std::string, std::shared_ptr<Db>> m_nDbs;
    static std::shared_ptr<Db> m_nCurrDb;
    static std::map<std::string, command> m_nCommand;

  public:
    Server()
    {
        std::cout << "class server constuct\n";
    }
    static Server &getServerInstace()
    {
        static Server m_nServer;
        return m_nServer;
    }
    void setCurrDb(const std::string &db)
    {
        auto p = m_nDbs.find(db);
        if (p == m_nDbs.end())
        {
            std::cout << db << " not exists\n";
            return;
        }
        m_nCurrDb = p->second;
    }
    static std::shared_ptr<Db> getCurrDb()
    {
        return m_nCurrDb;
    }
    static bool regitCommand(const std::string &n, command c)
    {
        m_nCommand[n] = c;
    }
    command findCommand(const std::string &n)
    {
        auto p = m_nCommand.find(n);
        if (p == m_nCommand.end())
        {
            std::cout << "command error:" << n << "\n";
            return nullptr;
        }
        return p->second;
    }
    ~Server()
    {
        std::cout << "class Server destory\n";
    }
};

std::shared_ptr<Db> Server::m_nCurrDb = nullptr;
std::map<std::string, command> Server::m_nCommand;

class Db
{
  private:
    std::string m_nName;
    std::map<std::string, std::shared_ptr<Dict>> m_nDicts;

  public:
    std::shared_ptr<Dict> findDict(const std::string dict)
    {
        auto p = m_nDicts.find(dict);
        if (p == m_nDicts.end())
        {
            return nullptr;
        }
        return p->second;
    }
};
#endif
