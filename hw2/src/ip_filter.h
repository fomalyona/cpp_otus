#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <iterator>

#include "ip_address.h"

namespace filtering_ip
{

    template<typename T>
    std::vector<T> split(const std::string& line, const char separator = '.')
    {
        std::vector<T> data;
        std::string s = line;

        size_t pos = 0;
        do
        {
            pos = s.find(separator);
            data.emplace_back(s.substr(0, pos));
            s.erase(0, pos + 1);
        }
        while ( pos != std::string::npos );

        return data;
    }

    template<typename T>
    std::vector<T> sort_by_greater( const std::vector<T>& in)
    {
        std::vector<T> result = in;

        std::sort(result.begin(), result.end(), std::greater<T>());

        return result;

    }

    template <typename Iterator, typename Predicate>
    void print(Iterator begin, Iterator end, Predicate pred)
    {
        for (Iterator it = begin; it != end; ++it)
        {
            if (pred(*it))
                std::cout << (*it) << std::endl;
        }
    }

    static std::vector<IpAddress> parse_from_in_stream()
    {
        std::vector<IpAddress> ip_pool;
        for(std::string line; std::getline(std::cin, line, '\n'); )
            ip_pool.emplace_back(split<IpAddress::Value>(split<std::string>(line, '\t').at(0)));

        return ip_pool;
    }

    void print(const std::vector<IpAddress> &ips)
    {
        print(ips.begin(), ips.end(),[](const IpAddress& ){return true;});
    }

    void print_by_first_second(const std::vector<IpAddress> &ips, int first , int second)
    {
        print(ips.begin(), ips.end(),[&](const IpAddress& address){
            return address.get().at(0).value == first &&
                   address.get().at(1).value == second;}
        );
    }

    void print_by_first(const std::vector<IpAddress> &ips, int by_num_element )
    {
        print(ips.begin(), ips.end(),[&](const IpAddress& address){
            return address.get().at(0).value == by_num_element;}
        );
    }

    void print_by_any(const std::vector<IpAddress> &ips, int by_num_element )
    {
        print(ips.begin(), ips.end(),[&](const IpAddress& address){
                  return std::any_of(address.cbegin(), address.cend(),
                                     [by_num_element](const IpAddress::Value& ip)
                                     { return ip.value == by_num_element; });
              }
        );
    }

    void run_filter()
    {
        auto data = parse_from_in_stream();

        data = sort_by_greater(data);
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