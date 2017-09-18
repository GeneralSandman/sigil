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
    m_pSaveFileIO->ioWrite(&n, sizeof(n));
}

int Persist::m_fSaveCode(int code)
{
    m_pSaveFileIO->ioWrite(&code, sizeof(code));
}

int Persist::m_fSaveString(const std::string &s)
{
    m_fSaveInt(s.size());
    m_pSaveFileIO->ioWrite(s.c_str(), s.size());
}

int Persist::m_fSaveKeyValue(const std::string &k, const std::string &v)
{
    m_fSaveString(k);
    m_fSaveString(v);
}

class Db;
int Persist::m_fSaveDb(std::shared_ptr<Db> d)
{
    //DB_CODE_SELECTDB+db_number+key_value
    std::string db_name = d->getName();
    int db_number = d->getNumber();

    m_fSaveCode(DB_CODE_SELECTDB);
    m_fSaveString(db_name);
    m_fSaveInt(db_number);

    int lists_num = d->m_nLists.size();
    int dicts_num = d->m_nDicts.size();

    std::cout << "db_name:" << db_name
              << ",db_number:" << db_number
              << ",lists num:" << lists_num
              << ",dicts num:" << dicts_num << std::endl;

    m_fSaveInt(lists_num);
    for (auto list : d->m_nLists)
        m_fSaveList(list.second);

    m_fSaveInt(dicts_num);
    for (auto dict : d->m_nDicts)
        m_fSaveDict(dict.second);
}

template <typename T>
class List;
int Persist::m_fSaveList(std::shared_ptr<List<std::string>> list)
{
    int len = list->getLen();
    if (!len) //list have no node,needn't to save this list
        return 0;
    m_fSaveCode(DB_CODE_LIST);
    m_fSaveString(list->getName());
    m_fSaveInt(len);

    std::cout << "list_name:" << list->getName()
              << ",list_len:" << len << std::endl;

    ListIter<std::string> iter(list.get(), AL_START_HEAD);
    ListNode<std::string> *t = nullptr;
    while ((t = iter.getListNext()) != nullptr)
    {
        m_fSaveString(t->m_nValue);
        std::cout << "save " << t->m_nValue << std::endl;
    }
}

int Persist::m_fSaveDict(std::shared_ptr<Dict<std::string, std::string>> dict)
{
    int size = dict->dictLen();
    if (!size)
        return 0;
    m_fSaveCode(DB_CODE_DICT);
    m_fSaveString(dict->getName());
    m_fSaveInt(size);

    std::cout << "dict_name:" << dict->getName()
              << ",dict_len:" << size << std::endl;

    DictIter<std::string, std::string> iter(dict.get());
    DictEntry<std::string, std::string> *t = nullptr;
    while ((t = iter.getDictNext()) != nullptr)
    {
        m_fSaveKeyValue(t->getKey(), t->getValue());
        std::cout << "save - " << t->getKey() << ":" << t->getValue() << std::endl;
    }
}

int Persist::m_fLoadInt(int &i)
{
    m_pLoadFileIO->ioRead(&i, sizeof(i));
}

int Persist::m_fLoadCode(int &i)
{
    m_pLoadFileIO->ioRead(&i, sizeof(i));
}

int Persist::m_fLoadString(std::string &s)
{
    //we have to know the s.size()
    int len = 0;
    m_fLoadInt(len);
    char *tmp = new char[len];
    m_pLoadFileIO->ioRead(tmp, len);
    for (int i = 0; i < len; i++)
        s += tmp[i];
    delete[] tmp;
}

int Persist::m_fLoadKeyValue(std::string &k, std::string &v)
{
    m_fLoadString(k);
    m_fLoadString(v);
}

int Persist::m_fLoadDb()
{
    int code;
    std::string db_name;
    int db_number;

    m_fLoadCode(code);
    m_fLoadString(db_name);
    m_fLoadInt(db_number);

    //create new datebase,
    //the init datebase is been overrideed;
    std::shared_ptr<Db> newdb = std::make_shared<Db>(db_name);
    Server::getServerInstace()->m_nDbs[db_name] = newdb;

    int lists_num = 0, dicts_num = 0;

    m_fLoadInt(lists_num);
    for (int i = 0; i < lists_num; i++)
        m_fLoadList(newdb);
    
    m_fLoadInt(dicts_num);    
    for (int i = 0; i < dicts_num; i++)
        m_fLoadDict(newdb);

    std::cout << "db_name:" << db_name
              << ",db_number:" << db_number
              << ",lists num:" << lists_num
              << ",dicts num:" << dicts_num << std::endl;
}

int Persist::m_fLoadList(std::shared_ptr<Db> db)
{
    int code;
    std::string list_name;
    int list_len;

    m_fLoadCode(code);
    m_fLoadString(list_name);
    m_fLoadInt(list_len);

    std::cout << "list_name:" << list_name
              << ",list_len:" << list_len << std::endl;

    shared_of_list p_list = db->getList(list_name);
    for (int i = 0; i < list_len; i++)
    {
        std::string value;
        m_fLoadString(value);
        std::cout << "add to list:" << value << std::endl;
        p_list->add_tail(value);
    }
}

int Persist::m_fLoadDict(std::shared_ptr<Db> db)
{
    int code;
    std::string dict_name;
    int dict_len;

    m_fLoadCode(code);
    m_fLoadString(dict_name);
    m_fLoadInt(dict_len);

    std::cout << "dict_name:" << dict_name
              << ",dict_len:" << dict_len << std::endl;

    shared_of_dict p_dict =
        db->getDict(dict_name);
    for (int i = 0; i < dict_len; i++)
    {
        std::string k, v;
        m_fLoadKeyValue(k, v);
        std::cout << "load - "
                  << k << ":" << v << std::endl;
        p_dict->dictSet(k, v);
    }
}

Persist::Persist(const std::string &file)
    : m_nRDBFile(file)
{
    LOG(Debug) << "class Persist constructor" << std::endl;
    m_pSaveFileIO = nullptr;
    m_pLoadFileIO = nullptr;
}

bool Persist::save()
{
    if (m_pSaveFileIO == nullptr)
        m_pSaveFileIO = new FileIO(100, m_nRDBFile, "wb");

    Server *server = Server::getServerInstace();
    std::string head = "Sigil";

    m_fSaveString(head);
    m_fSaveInt(server->getDbsNum());
    for (auto db : server->m_nDbs)
    {
        m_fSaveDb(db.second);
    }
    m_fSaveCode(DB_CODE_EOF);

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

    if (m_pLoadFileIO == nullptr)
        m_pLoadFileIO = new FileIO(100, m_nRDBFile, "r");

    std::string head;
    int eof;

    m_fLoadString(head);
    if (head != "Sigil")
        return false;

    int dbsNum = 0;
    m_fLoadInt(dbsNum);
    std::cout << "dbsNum:" << dbsNum << std::endl;

    for (int i = 0; i < dbsNum; i++)
    {
        m_fLoadDb();
    }
    m_fLoadCode(eof);

    return true;
}

Persist::~Persist()
{
    LOG(Debug) << "class Persist destructor" << std::endl;

    if (m_pSaveFileIO != nullptr)
    {
        delete m_pSaveFileIO;
        m_pSaveFileIO = nullptr;
    }
    if (m_pLoadFileIO != nullptr)
    {
        delete m_pLoadFileIO;
        m_pLoadFileIO = nullptr;
    }
}