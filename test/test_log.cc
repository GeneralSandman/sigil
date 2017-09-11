#include "../log.h"
#include <ctime>
#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
    {
        initLogger("log/debug.log",
                   "log/info.log",
                   "log/warn.log",
                   "log/error.log",
                   "log/fatal.log",
                   Debug);
        for (log_level l = Debug; l <= Fatal; l = log_level(l + 1))
        {
            setLogLevel(l);

            LOG(Debug) << endl;
            LOG(Info) << endl;
            LOG(Warning) << endl;
            LOG(Error) << endl;
            LOG(Fatal) << endl;

            sleep(2);
        }
    }
    std::cout << "main block\n";

    return 0;
}