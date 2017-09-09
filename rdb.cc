#include "rdb.h"
#include <fstream>
#include <iostream>
Persist::Persist(const std::string &file)
    : m_nRDBFile(file)
{
    m_nOut.open(file, std::ios::binary);
    m_nIn.open(file, std::ios::binary);
}

bool Persist::save()
{
    // std::string
    std::string first = "Sigil";
    int eof = RDB_OPCODE_EOF;
    
    m_nOut.write(first.c_str(), first.size());
    m_nOut.write((char *)&eof, sizeof(int));
}

bool Persist::bgsave()
{
}

Persist::~Persist()
{
    m_nOut.close();
    m_nIn.close();
}