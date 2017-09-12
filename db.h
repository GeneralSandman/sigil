#ifndef DB_H
#define DB_H
#include <string>
#include <fstream>

#define DB_OPCODE_SELECTDB 254
#define DB_OPCODE_EOF 255

class Persist
{
private:
  std::string m_nRDBFile;
  FILE *m_pFp;

public:
  Persist(const std::string &);
  bool save();
  bool bgsave();
  bool load();
  ~Persist();
};
#endif