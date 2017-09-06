#include "../log.h"
#include <ctime>
#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
    initLogger("info.log", "warn.log", "error.log");

    for (int i = 0; i < 4; i++)
    {
        LOG(Info) << i << endl;
        LOG(Warning) << i << endl;
        LOG(Error) << i << endl;

        sleep(1);
    }

    delete Logger::getLoggerInstance();
    return 0;
}