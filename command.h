#ifndef COMMAND_H
#define COMMAND_H

#include "sigil.h"
#include "exception.h"
#include <string>
#include <deque>
#include <boost/ptr_container/ptr_vector.hpp>

bool hisroryCommand(std::deque<std::string> &args);
bool helpCommand(std::deque<std::string> &args);

class Command
{
  private:
    Server *m_pServer;
    Db *m_pDb;
    char *m_pStr;
    std::string m_nName;
    std::deque<std::string> m_nArgs;
    int m_nMaxHistorys;
    boost::ptr_vector<std::string> m_nHistory;

    int m_fGetCommand();
    void m_fParseCommand();
    void m_fInvokeCommand();

    void m_fSaveCommand();

  public:
    Command(Server *s, int size = 50)
    {
        m_pServer = s;
        m_pStr = NULL;
        m_nMaxHistorys = size;
        m_nHistory.reserve(size);
    }
    void waitCommand()
    {

        m_nName = "";
        m_nArgs.clear();
        m_fGetCommand();
        if (m_pStr != nullptr)
        {
            m_fParseCommand();
            if (!m_nName.empty())
                m_fInvokeCommand();
        }
    }
    ~Command()
    {
        if (m_pStr)
        {
            free(m_pStr);
            m_pStr = NULL;
        }
    }
};

#endif
