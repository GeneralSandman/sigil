#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <deque>
#include <cstring>
#include <memory>
#include "sigil.h"
class Command
{
  private:
    std::shared_ptr<Server> m_nServer;
    std::shared_ptr<Db> m_nDb;
    char m_nStr[256];
    std::string m_nName;
    std::deque<std::string> m_nArgs;
    int m_fGetCommand()
    {
        std::cin.getline(m_nStr, 256, '\n');
    }
    void m_fParseCommand()
    {
        int length = strlen(m_nStr);
        std::string tmp;

        for (int i = 0; i < length; i++)
        {
            if (m_nStr[i] != ' ')
            {
                tmp += m_nStr[i];
            }
            else
            {
                if (!tmp.empty())
                    m_nArgs.push_back(tmp);
                tmp = "";
            }
        }
        if (!tmp.empty())
            m_nArgs.push_back(tmp);

        m_nName = m_nArgs.front();
        m_nArgs.pop_front();
    }
    void m_fInvokeCommand()
    {
        auto com = m_nServer->findCommand(m_nName);
        if (com != nullptr)
        {
            std::cout << "command error:" << m_nName << "\n";
            com(m_nArgs);
        }
    }

  public:
    Command(std::shared_ptr<Server> s){
        m_nServer=s;
    }
    void waitCommand()
    {
        m_fGetCommand();
        m_fParseCommand();
        m_fInvokeCommand();
    }
};

#endif // !COMMAND_H
