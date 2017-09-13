#include "../io.h"

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
#define COde 255

int loadString(std::string &a)
{
}
int main()
{
    FileIO fileio(100, "./dbfile/sigil.db");

    string s = "redis";
    int a = 123;
    int code = COde;

    fileio.ioWrite(s.c_str(), s.size());
    fileio.ioWrite(&a, sizeof(a));
    fileio.ioWrite(&code, sizeof(code));

    fileio.ioFlush();
    fileio.reset2Head();

    string ss;
    ss.resize(5);
    int aa;
    int code2;
    for (int i = 0; i < ss.size(); i++)
    {
        fileio.ioRead(&ss[i], 1);
    }
    fileio.ioRead(&aa, sizeof(aa));
    fileio.ioRead(&code2, sizeof(code2));

    cout << ss << endl
         << aa << endl
         << code2 << endl;

}
