#include "../rdb.h"

int main()
{
    Persist p("a.dat");
    p.save();
    return 0;
}