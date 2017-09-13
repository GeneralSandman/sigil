#include "persist.h"
#include "io.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

int Persist::m_fSaveInt(int n)
{
    m_pFileIO->ioWrite(&n, sizeof(n));
}

int Persist::m_fSaveCode(int code)
{
    m_pFileIO->ioWrite(&code, sizeof(code));
}

int Persist::m_fSaveString(const std::string &s)
{
    m_fSaveInt(s.size());
    m_pFileIO->ioWrite(s.c_str(), s.size());
}

int Persist::m_fSaveKeyValue(const std::string &, const std::string &)
{
}

int Persist::m_fSaveDb()
{
    //DB_CODE_SELECTDB+db_number+key_value
    int code = DB_CODE_SELECTDB;
    std::string db_name = "init";
    int db_number = 0;

    m_fSaveCode(code);
    m_fSaveString(db_name);
    m_fSaveInt(db_number);
}

int Persist::m_fSaveList() {}

int Persist::m_fSaveDict() {}

int Persist::m_fLoadInt(int &i)
{
    m_pFileIO->ioRead(&i, sizeof(i));
}

int Persist::m_fLoadCode(int &i)
{
    m_pFileIO->ioRead(&i, sizeof(i));
}

int Persist::m_fLoadString(std::string &s)
{
    //we have to know the s.size()
    int len = 0;
    m_fLoadInt(len);
    char *tmp = new char[len];
    m_pFileIO->ioRead(tmp, len);
    for (int i = 0; i < len; i++)
        s += tmp[i];
    delete[] tmp;
}

int Persist::m_fLoadKeyValue(std::string &, std::string &) {}

int Persist::m_fLoadDb()
{
    int code;
    std::string db_name;
    db_name.resize(4);
    int db_number;

    m_fLoadCode(code);
    m_fLoadString(db_name);
    m_fLoadInt(db_number);

    std::cout << "code:" << code << std::endl;
    std::cout << "db_name:" << db_name << std::endl;
    std::cout << "db_number:" << db_number << std::endl;
}

int Persist::m_fLoadList() {}

int Persist::m_fLoadDict() {}

Persist::Persist(const std::string &file)
    : m_nRDBFile(file)
{
    m_pFileIO = new FileIO(100, file);
}

bool Persist::save()
{

    std::string head = "Sigil";
    int eof = DB_CODE_EOF;

    m_fSaveString(head);
    m_fSaveInt(1); //db nums
    m_fSaveDb();
    m_fSaveCode(eof);

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
    m_fLoadDb();
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