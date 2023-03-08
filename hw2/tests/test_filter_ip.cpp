#include <fstream>

#include "../src/ip_filter.h"

#include "gtest/gtest.h"

#include <openssl/md5.h>


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

std::string md5_from_string(const std::string& in)
{
    auto str = in;
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<unsigned char*>(str.data()), str.size(), result);

    std::ostringstream out;
    out<<std::hex<<std::setfill('0');
    for(auto c: result)
        out<<std::setw(2)<<static_cast<int>(c);
    return out.str();
}

TEST(test_filter_ip, test_from_file)
{
    std::string in_file = "../ip_filter.tsv";

    static std::ifstream alt_cin;
    alt_cin.open (in_file.c_str(), std::ios::in | std::ios::binary);
    if (!alt_cin.fail() )
    {
        std::istream& s = alt_cin;

        auto data = filtering_ip::parse_from_in_stream(s);

        data = filtering_ip::sort_by_greater(data);

        std::stringstream buffer;

        std::streambuf *sbuf = std::cout.rdbuf();

        std::cout.rdbuf(buffer.rdbuf());

        filtering_ip::print(data);

        filtering_ip::print_by_first(data, 1);

        filtering_ip::print_by_first_second(data, 46, 70);

        filtering_ip::print_by_any(data, 46);

        std::cout.rdbuf(sbuf);

        std::string true_result =  "24e7a7b2270daee89c64d3ca5fb3da1a";

        ASSERT_EQ(true_result, md5_from_string(buffer.str()));

    }
    else
        std::cout << "failed open file: " << in_file << std::endl;

}
TEST( test_filter_ip, test_filter_ip)
{
   std::vector<IpAddress> data = {IpAddress({1,5,2,3}), // 0
                      IpAddress({1,43,2,3}), // 1
                      IpAddress({6,2,2,3}), // 2
                      IpAddress({1,3,46,33}), // 3
                      IpAddress({2,2,2,3}), // 4
                      IpAddress({1,29,168,152}), // 5
                      IpAddress({1,70,44,170}), // 6
                      IpAddress({46,70,29,76}) , // 7
                      IpAddress({146,101,163,119}), // 8
                      IpAddress({46,101,163,119}) };// 9

    data = filtering_ip::sort_by_greater(data);

    std::vector<IpAddress> true_data = {
                                         IpAddress({146,101,163,119}), // 8
                                         IpAddress({46,101,163,119}), // 9
                                         IpAddress({46,70,29,76}) , // 7
                                         IpAddress({6,2,2,3}), // 2
                                         IpAddress({2,2,2,3}), // 4
                                         IpAddress({1,70,44,170}), // 6
                                         IpAddress({1,43,2,3}), // 1
                                         IpAddress({1,29,168,152}), // 5
                                         IpAddress({1,5,2,3}), // 0
                                         IpAddress({1,3,46,33}), // 3
                                        };

    ASSERT_EQ(data, true_data);

    std::stringstream buffer;

    std::streambuf *sbuf = std::cout.rdbuf();

    std::cout.rdbuf(buffer.rdbuf());

    filtering_ip::print(data);

    std::cout.rdbuf(sbuf);

    std::string result = buffer.str();
    std::string true_result = "146.101.163.119\n46.101.163.119\n46.70.29.76\n6.2.2.3\n2.2.2.3\n1.70.44.170\n1.43.2.3\n1.29.168.152\n1.5.2.3\n1.3.46.33\n";

    ASSERT_EQ(result, true_result);

    buffer.str("");
    sbuf = std::cout.rdbuf();

    std::cout.rdbuf(buffer.rdbuf());

    filtering_ip::print_by_first(data, 1);

    std::cout.rdbuf(sbuf);

    std::string result_1 = buffer.str();
    std::string true_result_1 = "1.70.44.170\n1.43.2.3\n1.29.168.152\n1.5.2.3\n1.3.46.33\n";
    ASSERT_EQ(result_1, true_result_1);

    buffer.str("");
    sbuf = std::cout.rdbuf();

    std::cout.rdbuf(buffer.rdbuf());

    filtering_ip::print_by_first_second(data, 46, 70);

    std::cout.rdbuf(sbuf);

    std::string result_2 = buffer.str();
    std::string true_result_2 = "46.70.29.76\n";
    ASSERT_EQ(result_2, true_result_2);


    buffer.str("");
    sbuf = std::cout.rdbuf();

    std::cout.rdbuf(buffer.rdbuf());

    filtering_ip::print_by_any(data, 46);

    std::cout.rdbuf(sbuf);

    std::string result_3 = buffer.str();
    std::string true_result_3 = "46.101.163.119\n46.70.29.76\n1.3.46.33\n";
    ASSERT_EQ(result_3, true_result_3);

}


