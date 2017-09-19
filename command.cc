#include "command.h"
#include "log.h"
#include <string>
#include <deque>
#include <readline/readline.h>
#include <readline/history.h>

////////command api
int Command::m_fGetCommand()
{
    if (m_pStr)
    {
        free(m_pStr);
        m_pStr = NULL;
    }
    m_pStr = readline("^_^sigil> ");
    if (m_pStr && *m_pStr)
    {
        add_history(m_pStr);
        m_nHistory.push_back(new std::string(m_pStr));
        if (m_nHistory.size() == m_nMaxHistorys)
            m_fSaveCommand();
    }
}

void Command::m_fParseCommand()
{
    int length = strlen(m_pStr);
    std::string tmp;
    for (int i = 0; i < length; i++)
    {
        if (*(m_pStr + i) != ' ')
        {
            tmp += *(m_pStr + i);
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

    if (!m_nArgs.empty())
    {
        m_nName = m_nArgs.front();
        m_nArgs.pop_front();
    }
}

void Command::m_fInvokeCommand()
{
    auto com = m_pServer->findCommand(m_nName);
    if (com != nullptr)
    {
        com(m_nArgs);
    }
    else
    {
        std::cout << "(error) not command \"" << m_nName << "\"\n";
    }
}

void Command::m_fSaveCommand()
{
    for (auto t : m_nHistory)
    { //write command to file
        std::cout << t << t.size() << std::endl;
    }
    m_nHistory.clear();
}

bool hisroryCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (hisrory)" << std::endl;
}

bool helpCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (help)" << std::endl;
}
