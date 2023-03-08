#pragma once

#include <string>
#include <vector>

class IpAddress
{
public:

    struct Value
    {
    public:
        Value(const std::string& str) : value (std::stoi(str)){}

        Value(uint8_t num) : value(num){}

        ~Value() = default;
        
        uint8_t value;
    };

    IpAddress(std::vector<Value> ip) : _address(std::move(ip))
    {
        assert(_address.size() == ip_len);
    }

    ~IpAddress() = default;

    const std::vector<IpAddress::Value>& get() const
    {
        return _address;
    }

    auto begin() {
        return _address.begin();
    }

    auto end() {
        return _address.end();
    }

    const auto cbegin() const {
        return _address.cbegin();
    }

    const auto cend() const{
        return _address.cend();
    }

private:

    static constexpr int ip_len = 4;

    std::vector<IpAddress::Value> _address;

};

std::ostream& operator<<(std::ostream& out, const IpAddress& value)
{
    auto print = [&](const IpAddress::Value& n, const std::string& del=".") { out << static_cast<int>(n.value) << del; };
    std::for_each(value.cbegin(), value.cend()-1, print);
    print(*(value.cend()-1),"");
    return out;
}

bool operator<(const IpAddress::Value& a, const IpAddress::Value &b)
{
    return a.value < b.value;

}

bool operator>(const IpAddress::Value& a, const IpAddress::Value &b)
{
    return a.value > b.value;

}

bool operator==(const IpAddress::Value& a, const IpAddress::Value &b)
{
    return a.value == b.value;
}

bool operator!=(const IpAddress::Value& a, const IpAddress::Value &b)
{
    return a.value != b.value;
}

bool operator<(const IpAddress& a, const IpAddress &b)
{
    auto end1 = a.get().end();
    auto end2 = b.get().end();

    for (auto begin1 = a.get().begin(), begin2 = b.get().begin(); begin1 != end1 && begin2 != end2; ++begin1, ++begin2)
    {
        if (begin1->value != begin2->value)
            return begin1->value < begin2->value;
    }
    return end1->value < end2->value;

}

bool operator>(const IpAddress& a, const IpAddress &b)
{
    return b < a;
}

bool operator==(const IpAddress& a, const IpAddress &b)
{
    return b.get() == a.get();
}

bool operator!=(const IpAddress& a, const IpAddress &b)
{
    return b.get() != a.get();
}