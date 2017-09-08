#include "../dict.h"
#include "../log.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    {
        string d = "db";
        string key = "a";
        string value = "a";

        Dict<string, string> newdict(d);
        newdict.dictSet(key, value);
        cout << newdict.dictGet(key) << endl;

        newdict.dictSet(key, "123");
        cout << newdict.dictGet(key) << endl;
    }

    return 0;
}