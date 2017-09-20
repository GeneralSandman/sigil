#include "command.h"
#include "log.h"
#include "api.h"
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
    if (args.size() != 1)
    {
        std::cout << "(error) args error\n";
        return false;
    }

    // int num = 0;
    // if (isNum(args[0].c_str(), num))
    // {
    //     if (num == 0)
    //         num = 1;

    //     if (num > 0)
    //     {
    //         for (int i = 0; i < num; i++)
    //         {
    //             std::cout << "\t" << i + 1 << std::endl;
    //         }
    //     }
    //     else
    //     {
    //         for (int i = 0; i < num; i++)
    //         {
    //             std::cout << "\t-" << i + 1 << std::endl;
    //         }
    //     }
    // }
    // else
    // {
    //     if (args[0] == "a")
    //     { //cout all history
    //     }
    //     else if (args[0] == "c")
    //     { //storage command to file then clear history
    //     }
    // }
}

bool helpCommand(std::deque<std::string> &args)
{
    LOG(Info) << "command (help)" << std::endl;
    if (!args.empty())
    {
        std::cout << "(error) args error\n";
        return false;
    }
}
