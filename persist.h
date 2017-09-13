#ifndef PERSIST_H
#define PERSIST_H
#include <string>
#include "io.h"

#define DB_CODE_LIST 200
#define DB_CODE_DICT 210
#define DB_CODE_SELECTDB 254
#define DB_CODE_EOF 255

class Persist
{
private:
  std::string m_nRDBFile;
  FileIO *m_pFileIO;

  int m_fSaveInt(int);
  int m_fSaveCode(int);
  int m_fSaveString(const std::string &);
  int m_fSaveKeyValue(const std::string &, const std::string &);
  int m_fSaveDb();
  int m_fSaveList();
  int m_fSaveDict();

  int m_fLoadInt(int &);
  int m_fLoadCode(int &);
  int m_fLoadString(std::string &);
  int m_fLoadKeyValue(std::string &, std::string &);
  int m_fLoadDb();
  int m_fLoadList();
  int m_fLoadDict();

public:
  Persist(const std::string &);
  bool save();
  bool bgsave();
  bool load();
  ~Persist();
};
#endif