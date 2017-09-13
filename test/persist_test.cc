#include <iostream>
#include "../persist.h"

using namespace std;

int main()
{
    string file = "./dbfile/sigil.db";
    Persist p(file);

    p.save();
    p.load();

    return 0;
}