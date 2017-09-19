#include"command.h"
#include<string>
#include<deque>
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
        add_history(m_pStr);
}

void Command::m_fParseCommand()
{
    int length = strlen(m_pStr);
    std::string tmp;

    for (int i = 0; i < length; i++)
    {
        if (m_pStr[i] != ' ')
        {
            tmp += m_pStr[i];
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