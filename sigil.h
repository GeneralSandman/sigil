#include <iostream>
#include <map>
#include <vector>
#include <memory>

class Db;
class Server
{
  private:
    std::map<std::string, std::shared_ptr<Db>> m_nDbs;
};

class Db
{
  private:
    std::string name;
    

};