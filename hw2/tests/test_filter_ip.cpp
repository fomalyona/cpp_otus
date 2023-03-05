#include "../src/filter_ip_lib.h"

#include "gtest/gtest.h"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST( test_filter_ip_lib, test_filter_ip_lib)
{
       std::vector<IpAddress> data = {IpAddress({1,2,2,3}),
                          IpAddress({1,43,2,3}),
                          IpAddress({6,2,2,3}),
                          IpAddress({1,3,46,33}),
                          IpAddress({2,2,2,3}),
                          IpAddress({1,29,168,152}),
                          IpAddress({1,70,44,170}),
                          IpAddress({46,70,29,76}) ,
                          IpAddress({146,101,163,119}),
                          IpAddress({46,101,163,119}) };

    data = filtering_ip::sort(data);
//    filtering_ip::print(data);
    ASSERT_EQ(data.at(0), IpAddress({146,101,163,119}));


////       std::cout << "------------" << std::endl;
//    print(data);
////       std::cout << "------------" << std::endl;
//
//    print_by_first(data, 1);
////       std::cout << "------------" << std::endl;
//
//    print_by_first_second(data, 46, 70);
////       std::cout << "------------" << std::endl;
//
//    print_by_any(data, 46);
////    ASSERT_TRUE(version() > 0);

}
