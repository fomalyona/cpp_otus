#pragma once

#include <string>
#include <vector>


class Ip
{
public:
    Ip(const std::string& str)
    {
        ip = std::stoi(str);
    }

    Ip(uint8_t num)
    {
        ip = num;
    }
    ~Ip() = default;
    uint8_t ip;

};

std::ostream& operator<<(std::ostream& out, const Ip& value)
{
    out << std::to_string(value.ip);
    return out;
}

class IpAddress
{
public:
    typedef Ip value_type;
    IpAddress(std::vector<Ip> ip):_address(std::move(ip))
    {
        assert(_address.size() == 4);
    }

    ~IpAddress() = default;

    const std::vector<Ip>& get() const
    {
        return _address;
    }

    auto begin() {
        return _address.begin();
    }

    const auto begin() const{
        return _address.begin();
    }


    auto end() {
        return _address.end();
    }

    const auto end() const{
        return _address.end();
    }

    const auto cbegin() const {
        return _address.cbegin();
    }

    const auto cend() const{
        return _address.cend();
    }

private:
    std::vector<Ip> _address;

};


std::ostream& operator<<(std::ostream& out, const IpAddress& value)
{
    auto print = [&](const Ip& n, const std::string& del=".") { out << n << del; };
    std::for_each(value.cbegin(), value.cend()-1, print);
    print(*(value.end()-1),"");
    return out;
}

bool operator<(const IpAddress& a, const IpAddress &b)
{
    auto end1 = a.get().end();
    auto end2 = b.get().end();

    for (auto begin1 = a.get().begin(), begin2 = b.get().begin(); begin1 != end1 && begin2!=end2; ++begin1, ++begin2)
    {
        if (begin1->ip != begin2->ip)
            return begin1->ip < begin2->ip;
    }
    return end1->ip < end2->ip;

}

bool operator>(const IpAddress& a, const IpAddress &b)
{
    return b < a;
}

bool operator==(const IpAddress& a, const IpAddress &b)
{
    return !(b < a) && !(a < b);
}