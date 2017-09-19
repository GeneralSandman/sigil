#ifndef COMMAND_H
#define COMMAND_H

#include "sigil.h"
#include <string>
#include <deque>

class Command
{
  private:
    Server *m_pServer;
    Db *m_pDb;
    char *m_pStr;
    std::string m_nName;
    std::deque<std::string> m_nArgs;

    int m_fGetCommand();
    void m_fParseCommand();
    void m_fInvokeCommand();

  public:
    Command(Server *s)
    {
        m_pServer = s;
        m_pStr = NULL;
    }
    void waitCommand()
    {
        m_nName = "";
        m_nArgs.clear();
        m_fGetCommand();
        m_fParseCommand();
        m_fInvokeCommand();
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
