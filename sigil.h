#ifndef SIGIL_H
#define SIGIL_H

#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <memory>
#include <deque>
#include "dict.h"

bool listDbsCommand(std::deque<std::string> &args);
bool createDbCommand(std::deque<std::string> &args);
bool selectCurrDbCommand(std::deque<std::string> &args);
bool showCurrDbCommand(std::deque<std::string> &args);

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
  static Server *serverInstance;
  std::map<std::string, std::shared_ptr<Db>> m_nDbs;
  static std::shared_ptr<Db> m_nCurrDb;
  static std::map<std::string, command> m_nCommand;
  Server();

public:
  void listDbs(void);
  bool createDb(const std::string &db);
  bool deleteDb(const std::string &db);
  bool selectCurrDb(const std::string &db);
  void showCurrDb(void);
  static Server *getServerInstace()
  {
    if (serverInstance == nullptr)
      serverInstance = new Server();

    return serverInstance;
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
  Server *m_pServer;
  Db *m_pDb;
  char m_nStr[256];
  std::string m_nName;
  std::deque<std::string> m_nArgs;

  int m_fGetCommand();
  void m_fParseCommand();
  void m_fInvokeCommand();

public:
  Command(Server *s)
  {
    m_pServer = s;
  }
  void waitCommand()
  {
    memset(m_nStr, 0, 256);
    m_nName = "";
    m_nArgs.clear();
    m_fGetCommand();
    m_fParseCommand();
    m_fInvokeCommand();
  }
};

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
