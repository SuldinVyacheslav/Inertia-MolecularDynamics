// tests.cpp
#include <gtest/gtest.h>
#include <math.h>
#include <thread>

#include "../Vector.h"


TEST(SquareRootTest, PositiveNos)
{
    ASSERT_EQ(Vector(1,1,1).x, Vector(1,1,1).x);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}