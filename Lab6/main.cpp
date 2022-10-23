#include "gtest/gtest.h"
#include "poly.h"
#include <iostream>

TEST(polyTest, poly) {
    Polynom<2, 3, 4> test;
    constexpr int tst1 = test.getValue(2);
    constexpr int tst2 = test.getValue(3);

    EXPECT_EQ(tst1, 24);
    EXPECT_EQ(tst2, 47);
}

int main(int argc, char **argv) {
    Polynom<1, 2, 3> test;

    constexpr int ts = test.getValue(2);

    std::cout << ts << std::endl;
    std::cout << test << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    //return 0;
}
