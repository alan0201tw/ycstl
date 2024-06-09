
#include <gtest/gtest.h>

#include "ycstl.hpp"

TEST(set, basic) {
    auto testSet = ycstl::YcSet<int> {};
    EXPECT_TRUE(testSet.isSorted());
    EXPECT_TRUE(testSet.isUnique());
}
