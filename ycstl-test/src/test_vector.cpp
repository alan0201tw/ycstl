
#include <gtest/gtest.h>

#include "ycstl.hpp"

TEST(vector, basic) {
    auto testVector = ycstl::YcVector<int> {};
    for (int i = 10; i >= 9; --i) {
        testVector.emplace_back(i);
    }
    EXPECT_FALSE(testVector.isSorted());
    EXPECT_FALSE(testVector.isUnique());

    const auto testSortedVector = testVector.getSortedVector();
    EXPECT_TRUE(std::is_sorted(testSortedVector.cbegin(), testSortedVector.cend()));
    EXPECT_TRUE(testSortedVector.isSorted());
    EXPECT_FALSE(testSortedVector.isUnique());
}
