
#include <gtest/gtest.h>

#include "ycstl.hpp"

TEST(vector, basic) {
    constexpr auto MaxElement = 10;
    auto testVector = ycstl::YcVector<int> {};
    for (int i = MaxElement; i >= 0; --i) {
        testVector.emplace_back(i);
    }
    EXPECT_FALSE(testVector.isSorted());
    EXPECT_FALSE(testVector.isUnique());

    const auto testSortedVector = testVector.getSortedVector();
    for (int i = 0; i < testSortedVector.size(); ++i) {
        EXPECT_EQ(i, testSortedVector.at(i));
    }
    EXPECT_TRUE(std::is_sorted(testSortedVector.cbegin(), testSortedVector.cend()));
    EXPECT_TRUE(testSortedVector.isSorted());
    EXPECT_FALSE(testSortedVector.isUnique());
}
