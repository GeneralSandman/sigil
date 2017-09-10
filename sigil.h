#ifndef SIGIL_H
#define SIGIL_H

#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <memory>
#include <deque>
#include "dict.h"
#include "list.h"

bool listDbsCommand(std::deque<std::string> &args);
bool createDbCommand(std::deque<std::string> &args);
bool deleteDbCommand(std::deque<std::string> &args);
bool selectCurrDbCommand(std::deque<std::string> &args);
bool showCurrDbCommand(std::deque<std::string> &args);
bool quitCommand(std::deque<std::string> &args);

template <typename K, typename V>
class Dict;

typedef bool (*command)(std::deque<std::string> &);
typedef std::shared_ptr<Dict<std::string, std::string>> shared_of_dict;
typedef std::shared_ptr<List<std::string>> shared_of_list;
class Db
{
private:
  int m_nNumber;
  std::string m_nName;

  std::string m_nPrevDict; //store the prev mainpulated dict
  shared_of_dict m_pPrevDict;
  std::map<std::string, shared_of_dict> m_nDicts;

  std::string m_nPrevList; //store the prev mainpulated list
  shared_of_list m_pPrevList;
  std::map<std::string, shared_of_list> m_nLists;

public:
  Db(const std::string &name);
  std::string &getName();
  int getNumber();
  shared_of_dict findDict(const std::string &dict);
  shared_of_list findList(const std::string &list);
  ~Db();
};

class Server
{
private:
  static Server *m_pServerInstance;
  int m_nDbsNum;
  std::map<std::string, std::shared_ptr<Db>> m_nDbs;
  static std::shared_ptr<Db> m_nCurrDb;
  static std::map<std::string, command> m_nCommand;
  bool m_nRun;
  Server();

public:
  void listDbs(void);
  bool createDb(const std::string &db);
  bool deleteDb(const std::string &db);
  bool selectCurrDb(const std::string &db);
  void showCurrDb(void);

  int getDbsNum() { return m_nDbsNum; }
  bool increDbsNum() { m_nDbsNum++; }
  static Server *getServerInstace()
  {
    LOG(Debug) << std::endl;
    if (m_pServerInstance == nullptr)
      m_pServerInstance = new Server();

    return m_pServerInstance;
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
  bool runing(void)
  {
    //quit sigil
    return m_nRun;
  }
  void stop(void)
  {
    m_nRun = false;
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

#define RegisterCommand(name, c) \
  Server::regitCommand(name, c)

#endif
