#ifndef PERSIST_H
#define PERSIST_H
#include <string>
#include <memory>
#include "io.h"

#define DB_CODE_LIST 200
#define DB_CODE_DICT 210
#define DB_CODE_SELECTDB 254
#define DB_CODE_EOF 255

class Db;
template <typename T>
class List;
template <typename K, typename V>
class Dict;
class Persist
{
private:
  std::string m_nRDBFile;
  FileIO *m_pFileIO;

  int m_fSaveInt(int);
  int m_fSaveCode(int);
  int m_fSaveString(const std::string &);
  int m_fSaveKeyValue(const std::string &, const std::string &);
  int m_fSaveDb(std::shared_ptr<Db>);
  int m_fSaveList(std::shared_ptr<List<std::string>>);
  int m_fSaveDict(std::shared_ptr<Dict<std::string, std::string>>);

  int m_fLoadInt(int &);
  int m_fLoadCode(int &);
  int m_fLoadString(std::string &);
  int m_fLoadKeyValue(std::string &, std::string &);
  int m_fLoadDb(std::shared_ptr<Db>);
  int m_fLoadList(std::shared_ptr<List<std::string>>);
  int m_fLoadDict(std::shared_ptr<Dict<std::string, std::string>>);

public:
  Persist(const std::string &);
  bool save();
  bool bgsave();
  bool load();
  ~Persist();
};
#endif