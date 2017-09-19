#include <iostream>
#include <deque>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <boost/ptr_container/ptr_vector.hpp>

using namespace std;

char *m_pStr = NULL; //终端输入字符串
boost::ptr_vector<std::string> m_nHistory;

char *ReadCmdLine()
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
        if (m_nHistory.size() == 5)
        {
            for (auto t : m_nHistory)
            { //write command to file
                std::cout << t << t.size() << std::endl;
            }
            m_nHistory.clear();
        }
    }
}

std::deque<std::string> m_nArgs;

int main(void)
{
    while (1)
    {
        ReadCmdLine();
        // if (m_pStr != nullptr)
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

            for (auto t : m_nArgs)
                cout << "-" << t;
            m_nArgs.clear();
        }
    }

    if (m_pStr)
    {
        free(m_pStr);
        m_pStr = NULL;
    }

    return 0;
}
