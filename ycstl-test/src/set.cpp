
#include <gtest/gtest.h>

#include "ycstl.hpp"

TEST(set, basic) {
    auto testSet = ycstl::ycset<int> {};
    EXPECT_TRUE(testSet.is_sorted());
}
