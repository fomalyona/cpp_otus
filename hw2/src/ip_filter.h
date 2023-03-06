#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <iostream>
#include <algorithm>

#include "ip.h"

namespace filtering_ip
{
    static constexpr int ip_size = 4;
    static constexpr int input_line_size = 3;

    template<typename T>
    std::vector<T> split(const std::string& line, const char separator = '.')
    {
        std::vector<T> ip_address;
        std::string s = line;

        size_t pos = 0;
        do
        {
            pos = s.find(separator);
            ip_address.emplace_back(s.substr(0, pos));
            s.erase(0, pos + 1);
        }
        while ( pos != std::string::npos );

        return ip_address;
    }

    std::vector<IpAddress> sort( const std::vector<IpAddress>& in)
    {
        std::vector<IpAddress> result = in;

        auto predicate_reverse = [](const IpAddress& a, const IpAddress& b){
            return a > b;
        };
        std::sort(result.begin(), result.end(), predicate_reverse);
        return result;

    }

    static std::vector<IpAddress> get_data()
    {
        std::vector<IpAddress> ip_pool;
        for(std::string line; std::getline(std::cin, line, '\n'); )
            ip_pool.emplace_back(split<Ip>(split<std::string>(line, '\t').at(0)));

        return ip_pool;
    }

    void print(const std::vector<IpAddress> &ips)
    {
        for(auto &address: ips)
        {
            std::cout << address << std::endl;
        }

    }

    void print_by_first_second(const std::vector<IpAddress> &ips, int first , int second)
    {
        for(auto &address: ips)
        {
            if (address.get().at(0).ip == first && address.get().at(1).ip == second  )
                std::cout << address << std::endl;
        }

    }

    void print_by_first(const std::vector<IpAddress> &ips, int by_num_element )
    {
        for(auto &address: ips)
        {
            if (address.get().at(0).ip == by_num_element)
                std::cout << address << std::endl;
        }

    }

    void print_by_any(const std::vector<IpAddress> &ips, int by_num_element )
    {

        for(auto &address: ips)
        {
            if (std::any_of(address.cbegin(), address.cend(), [by_num_element](const Ip& ip) { return ip.ip == by_num_element; }))
                std::cout << address << std::endl;
        }

    }

    void filter()
    {
        auto data = get_data();
//       std::vector<IpAddress> data = {IpAddress({1,2,2,3}),
//                          IpAddress({1,43,2,3}),
//                          IpAddress({6,2,2,3}),
//                          IpAddress({1,3,46,33}),
//                          IpAddress({2,2,2,3}),
//                                      IpAddress({ 1,29,168,152}),
//                                      IpAddress({1,70,44,170}),
//                                      IpAddress({46,70,29,76}) ,
//                                      IpAddress({46,101,163,119}) };

        data = sort(data);
//       std::cout << "------------" << std::endl;
        print(data);
//       std::cout << "------------" << std::endl;

        print_by_first(data, 1);
//       std::cout << "------------" << std::endl;

        print_by_first_second(data, 46, 70);
//       std::cout << "------------" << std::endl;

        print_by_any(data, 46);

    }

} // namespace filtering_ip