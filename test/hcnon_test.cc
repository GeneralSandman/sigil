#include <leatherman/locale/locale.hpp>
#include <iostream>


int main()
{
    std::cout << leatherman::locale::translate("This is translated") << std::endl;
    std::cout << leatherman::locale::format("This is {1} translated message", 1) << std::endl;

    return 0;
}