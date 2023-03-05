#include "filter_ip_lib.h"

#include <iostream>

int main (int, char **)
{
    try
    {
        filtering_ip::filter();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

