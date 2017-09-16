#include <iostream>
#include "../persist.h"

using namespace std;

int main()
{
    {

        string file = "/home/li/sigil/test/dbfile/sigil.db";
        Persist p(file);

        p.m_fSaveInt(33);
        string s = "sigil";
        p.m_fSaveString(s);
        p.m_fSaveCode(DB_CODE_SELECTDB);

        p.m_pSaveFileIO->reset2Head();
    }
    {

        string file = "/home/li/sigil/test/dbfile/sigil.db";
        Persist p(file);

        int res = 0;
        string s = "";
        int code = 0;

        p.m_fLoadInt(res);
        p.m_fLoadString(s);
        p.m_fLoadCode(code);

        cout << res << endl;
        cout << s << endl;
        cout << code << endl;
    }

    // p.save();
    // p.load();
    return 0;
}