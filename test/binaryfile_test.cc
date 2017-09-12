#include <iostream>
#include <fstream>

using namespace std;
#define RDB_OPCODE_EOF 255
int main()
{
    std::string file = "a.dat";
    std::ofstream m_nOut(file, std::ios::binary);
    std::string first = "Sigil";

    m_nOut.write(first.c_str(), first.size());
    int n = RDB_OPCODE_EOF;
    m_nOut.write((char *)&n, sizeof(int));
    m_nOut.close();
    // std::ifstream fin("a.dat", std::ios::binary);
    // char szBuf[888] = {0};
    // fin.read(szBuf,888);
    // std::cout << "str = " << szBuf << std::endl;
    // fin.close();

    return 0;
}