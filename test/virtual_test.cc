#include <iostream>
#include <string>
#include <execinfo.h>
#include "../log.h"

using namespace std;

class Basic
{
  protected:
    virtual void m_fF1(void)
    {
        LOG(Debug) << "B" << std::endl;
    }
    virtual void m_fF2(void)
    {
        LOG(Debug) << "B" << std::endl;
    }
    virtual void m_fF3(void)
    {
        LOG(Debug) << "B" << std::endl;
    }

  public:
    void f1()
    {
        LOG(Debug) << std::endl;
        m_fF1();
    }
    void f2()
    {
        LOG(Debug) << std::endl;
        m_fF3();
    }
    void f3()
    {
        LOG(Debug) << std::endl;
        m_fF3();
    }
};

class Drive : public Basic
{
  protected:
    virtual void m_fF1(void)
    {
        LOG(Debug) << "D" << std::endl;
        
    }
    virtual void m_fF2(void)
    {
        LOG(Debug) << "D" << std::endl;
        
    }
    virtual void m_fF3(void)
    {
        LOG(Debug) << "D" << std::endl;
        
    }
};

int main()
{
    class Basic b;
    class Drive d;

    b.f1();
    b.f2();
    b.f3();

    std::cout << "------\n";

    d.f1();
    d.f2();
    d.f3();

    return 0;
}