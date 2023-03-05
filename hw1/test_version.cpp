#include "lib.h"

#include "gtest/gtest.h"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST( test_version, test_version)
{
    ASSERT_TRUE(version() > 0);

}
