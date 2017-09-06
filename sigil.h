#ifndef SIGIL_H
#define SIGIL_H

#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <deque>
#include "dict.h"

template <typename K, typename V>
class Dict;

typedef bool (*command)(std::deque<std::string> &);
typedef std::shared_ptr<Dict<std::string, std::string>> shared_of_dict;

class Db
{
private:
  std::string m_nName;
  std::map<std::string, shared_of_dict> m_nDicts;

public:
  Db(const std::string &name);
  std::string &getName();
  std::shared_ptr<Dict<std::string, std::string>> findDict(const std::string dict);
  ~Db();
};

class Server
{
private:
  std::map<std::string, std::shared_ptr<Db>> m_nDbs;
  static std::shared_ptr<Db> m_nCurrDb;
  static std::map<std::string, command> m_nCommand;

public:
  Server();
  void listDbs(void);
  bool createDb(const std::string &db);
  bool selectCurrDb(const std::string &db);
  void showCurrDb(void);
  static Server &getServerInstace()
  {
    static Server m_nServer;
    return m_nServer;
  }
  void setCurrDb(const std::string &db);
  static std::shared_ptr<Db> getCurrDb()
  {
    return m_nCurrDb;
  }
  static bool regitCommand(const std::string &n, command c)
  {
    m_nCommand[n] = c;
  }
  command findCommand(const std::string &n);
  ~Server();
};

class Command
{
private:
  std::shared_ptr<Server> m_pServer;
  std::shared_ptr<Db> m_pDb;
  char m_nStr[256];
  std::string m_nName;
  std::deque<std::string> m_nArgs;

  int m_fGetCommand()
  {
    std::cin.getline(m_nStr, 256, '\n');
  }
  void m_fParseCommand()
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
  void m_fInvokeCommand()
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

public:
  Command(std::shared_ptr<Server> s)
  {
    m_pServer = s;
  }
  void waitCommand()
  {
    m_fGetCommand();
    m_fParseCommand();
    m_fInvokeCommand();
  }
};

typedef bool (*command)(std::deque<std::string> &);

class RegisterAction
{
public:
  RegisterAction(const std::string &name, command c)
  {
    Server::regitCommand(name, c);
    std::cout << "register " << name << " function\n";
  }
};

#define RegisterCommand(name, c) \
  RegisterAction Rigist##name(name, c)

#endif
