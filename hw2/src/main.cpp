#include "ip_filter.h"

#include <iostream>

int main (int, char **)
{
    try
    {
        filtering_ip::run_filter();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

