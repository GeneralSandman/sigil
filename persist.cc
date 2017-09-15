#include "persist.h"
#include "sigil.h"
#include "io.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <memory>

int Persist::m_fSaveInt(int n)
{
    LOG(Debug) << std::endl;
    m_pFileIO->ioWrite(&n, sizeof(n));
}

int Persist::m_fSaveCode(int code)
{
    LOG(Debug) << std::endl;
    m_pFileIO->ioWrite(&code, sizeof(code));
}

int Persist::m_fSaveString(const std::string &s)
{
    LOG(Debug) << std::endl;
    m_fSaveInt(s.size());
    m_pFileIO->ioWrite(s.c_str(), s.size());
}

int Persist::m_fSaveKeyValue(const std::string &k, const std::string &y)
{
    LOG(Debug) << std::endl;
}

class Db;
int Persist::m_fSaveDb(std::shared_ptr<Db> d)
{
    LOG(Debug) << std::endl;

    //DB_CODE_SELECTDB+db_number+key_value
    std::string db_name = d->getName();
    int db_number = d->getNumber();

    m_fSaveCode(DB_CODE_SELECTDB);
    m_fSaveString(db_name);
    m_fSaveInt(db_number);

    for (auto list : d->m_nLists)
        m_fSaveList(list.second);
    for (auto dict : d->m_nDicts)
        m_fSaveDict(dict.second);
}

template <typename T>
class List;
int Persist::m_fSaveList(std::shared_ptr<List<std::string>> list)
{
    LOG(Debug) << "save list\n";
}

int Persist::m_fSaveDict(std::shared_ptr<Dict<std::string, std::string>> dict)
{
    LOG(Debug) << "save dict\n";
}

int Persist::m_fLoadInt(int &i)
{
    LOG(Debug) << std::endl;
    m_pFileIO->ioRead(&i, sizeof(i));
}

int Persist::m_fLoadCode(int &i)
{
    LOG(Debug) << std::endl;
    m_pFileIO->ioRead(&i, sizeof(i));
}

int Persist::m_fLoadString(std::string &s)
{
    LOG(Debug) << std::endl;
    //we have to know the s.size()
    int len = 0;
    m_fLoadInt(len);
    char *tmp = new char[len];
    m_pFileIO->ioRead(tmp, len);
    for (int i = 0; i < len; i++)
        s += tmp[i];
    delete[] tmp;
}

int Persist::m_fLoadKeyValue(std::string &k, std::string &v)
{
    LOG(Debug) << std::endl;
}

int Persist::m_fLoadDb(std::shared_ptr<Db> db)
{
    LOG(Debug) << std::endl;

    // int code;
    // std::string db_name;
    // db_name.resize(4);
    // int db_number;

    // m_fLoadCode(code);
    // m_fLoadString(db_name);
    // m_fLoadInt(db_number);

    // std::cout << "code:" << code << std::endl;
    // std::cout << "db_name:" << db_name << std::endl;
    // std::cout << "db_number:" << db_number << std::endl;
}

int Persist::m_fLoadList(std::shared_ptr<List<std::string>> list)
{
    LOG(Debug) << std::endl;
    
}

int Persist::m_fLoadDict(std::shared_ptr<Dict<std::string, std::string>> dict)
{
    LOG(Debug) << std::endl;
    
}

Persist::Persist(const std::string &file)
    : m_nRDBFile(file)
{
    LOG(Debug) << std::endl;
    
    m_pFileIO = new FileIO(100, file);
}

bool Persist::save()
{
    Server *server = Server::getServerInstace();
    std::string head = "Sigil";

    m_fSaveString(head);
    m_fSaveInt(server->getDbsNum()); //db nums
    //save all datebases
    for (auto db : server->m_nDbs)
    {
        m_fSaveDb(db.second);
    }
    m_fSaveCode(DB_CODE_EOF);

    m_pFileIO->reset2Head();
    return true;
}

bool Persist::bgsave()
{
    //fork() and the child process to save the
    //memoey to the disk

    int p = fork();
    if (p > 0)
    {
        //????
    }
    else if (p == 0)
    {
        if (save())
            _exit(0);
    }
    else
    {
    }
}

bool Persist::load()
{
    std::string head;
    head.resize(5);
    int eof;

    m_fLoadString(head);
    // m_fLoadDb();
    m_fLoadCode(eof);

    std::cout << "head:" << head << std::endl;
    std::cout << "eof:" << eof << std::endl;

    m_pFileIO->reset2Head();

    return true;
}

Persist::~Persist()
{
    delete m_pFileIO;
    m_pFileIO = nullptr;
}