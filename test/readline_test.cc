#include <readline/readline.h>
#include <readline/history.h>

#include <iostream>
#include <stdlib.h>
using namespace std;

#include <readline/readline.h>
#include <readline/history.h>

char *pszLineRead = NULL; //终端输入字符串

char *ReadCmdLine()
{
    if (pszLineRead)
    {
        free(pszLineRead);
        pszLineRead = NULL;
    }
    pszLineRead = readline("^_^sigil> ");
    if (pszLineRead && *pszLineRead)
        add_history(pszLineRead);
    return pszLineRead;
}

int main(void)
{
    while (1)
    {
        char *pszCmdLine = ReadCmdLine();
        std::cout << pszCmdLine << std::endl;
    }
    if (pszLineRead)
    {
        free(pszLineRead);
        pszLineRead = NULL;
    }

    return 0;
}
