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
bool saveCommand(std::deque<std::string> &args);
bool bgsaveCommand(std::deque<std::string> &args);
// bool loadCommand(std::deque<std::string> &args);

template <typename K, typename V>
class Dict;

typedef bool (*command)(std::deque<std::string> &);
typedef std::shared_ptr<Dict<std::string, std::string>> shared_of_dict;
typedef std::shared_ptr<List<std::string>> shared_of_list;
class Db
{
private:
  static int m_nDbsNum;
  static int m_nCreatedDbs;
  int m_nNumber;
  std::string m_nName;

  std::map<std::string, shared_of_dict> m_nDicts;
  std::map<std::string, shared_of_list> m_nLists;

public:
  Db(const std::string &name);
  std::string &getName() { return m_nName; }
  int getNumber() { return m_nNumber; }
  shared_of_dict findDict(const std::string &dict);
  shared_of_dict getDict(const std::string &dict);
  shared_of_list findList(const std::string &list);
  shared_of_list getList(const std::string &list);

  ~Db();

  friend class Server;
  friend class Persist;
};

class Persist;

class Server
{
private:
  static Server *m_pServerInstance;
  static std::string m_nDbFile;
  std::shared_ptr<Persist> m_pPersist;
  std::map<std::string, std::shared_ptr<Db>> m_nDbs;
  static std::shared_ptr<Db> m_nCurrDb;
  static std::map<std::string, command> m_nCommand;
  bool m_nRun;
  std::string m_nPersistFile;
  Server();
  void check();

public:
  void listDbs(void);
  bool createDb(const std::string &db);
  bool deleteDb(const std::string &db);
  bool selectCurrDb(const std::string &db);
  void showCurrDb(void);

  int getDbsNum() { return Db::m_nDbsNum; }
  static Server *getServerInstace()
  {
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
  bool runing(void) { return m_nRun; }
  void stop(void) { m_nRun = false; }
  command findCommand(const std::string &n);
  bool save();
  bool bgsave();
  bool load();
  ~Server();

  friend class Persist;
};



#define RegisterCommand(name, c) \
  Server::regitCommand(name, c)

#endif
