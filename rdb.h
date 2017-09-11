#ifndef RDB_H
#define RDB_H
#include <string>
#include <fstream>

#define RDB_OPCODE_SELECTDB 254
#define RDB_OPCODE_EOF 255

class Persist
{
  private:
    std::string m_nRDBFile;
    std::ofstream m_nOut;
    std::ifstream m_nIn;

  public:
    Persist(const std::string &);
    bool save();
    bool bgsave();
    bool load();
    ~Persist();
};
#endif