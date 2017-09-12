#include "db.h"
#include "io.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
Persist::Persist(const std::string &file)
    : m_nRDBFile(file),
      m_pFp(nullptr)
{
    //in constructor,we need't invoke open()
    //beacause we init class but not use it immeditly
}

bool Persist::save()
{
    m_pFp = fopen(m_nRDBFile.c_str(), "wb+");
    FileIO fileio(100, m_pFp);

    std::string first = "Sigil";
    int eof = RDB_OPCODE_EOF;

    fclose(m_pFp);
}

bool Persist::bgsave()
{
    m_pFp = fopen(m_nRDBFile.c_str(), "wb+");
    FileIO fileio(100, m_pFp);

    //fork() and the child process to save the
    //memoey to the disk

    fclose(m_pFp);
}

bool Persist::load()
{
    m_pFp = fopen(m_nRDBFile.c_str(), "wb+");
    FileIO fileio(100, m_pFp);

    fclose(m_pFp);
}

Persist::~Persist()
{
}