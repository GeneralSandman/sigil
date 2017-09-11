#include "rdb.h"
#include <fstream>
#include <iostream>
Persist::Persist(const std::string &file)
    : m_nRDBFile(file)
{
    //in constructor,we need't invoke open()
    //beacause we init class but not use it immeditly
}

bool Persist::save()
{
    m_nOut.open(m_nRDBFile, std::ios::binary);

    // std::string
    std::string first = "Sigil";
    int eof = RDB_OPCODE_EOF;

    m_nOut.write(first.c_str(), first.size());
    m_nOut.write((char *)&eof, sizeof(int));

    m_nOut.close();
}

bool Persist::bgsave()
{
    m_nOut.open(m_nRDBFile, std::ios::binary);

    //fork() and the child process to save the
    //memoey to the disk

    m_nOut.close();
}

bool Persist::load()
{
    m_nIn.open(m_nRDBFile, std::ios::binary);

    m_nIn.close();
}

Persist::~Persist()
{
}