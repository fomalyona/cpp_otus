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

        bool operator>(const Value& other) const
        {
            return value > other.value;
        }

        bool operator<(const Value& other) const
        {
            return value < other.value;
        }

        bool operator==(const Value& other) const
        {
            return value == other.value;
        }

        bool operator!=(const Value& other) const
        {
            return value != other.value;
        }
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

    bool operator>(const IpAddress& other) const
    {
        return _address > other._address;
    }

    bool operator<(const IpAddress& other) const
    {
        return _address < other._address;
    }

    bool operator==(const IpAddress& other) const
    {
        return _address == other._address;
    }

    bool operator!=(const IpAddress& other) const
    {
        return _address != other._address;
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
