#include "../io.h"

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

int main()
{
    FILE *f = fopen("./dbfile/sigil.db", "wb+");
    FileIO fileio(100, f);

    char s[] = "redis";
    int a = 123;
    fileio.ioWrite(s, strlen(s));
    fileio.ioWrite(&a, sizeof(a));
    fileio.ioFlush();

    fileio.reset2Head();

    char ss[6];
    int aa;
    fileio.ioRead(ss, 5);
    ss[5] = '\0';
    fileio.ioRead(&aa, sizeof(aa));

    cout << ss << endl
         << aa << endl;

    fclose(f);
}
