
#include <gtest/gtest.h>

#include <set>
#include <unordered_set>

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

TEST(vector, isSubsetOf) {
    const auto testVector0 = ycstl::YcVector<int> {0, 1, 2};
    const auto testVector1 = ycstl::YcVector<int> {10, 11, 12, 20};
    const auto stlSet = std::set<int> {10, 11, 12, 20, 21, 22, 23, 24};
    EXPECT_FALSE(testVector0.isSubsetOf(stlSet));
    EXPECT_TRUE(testVector1.isSubsetOf(stlSet));

    const auto stlUnordederSet = std::unordered_set<int> {0, 1, 2, 3, 4, 5};
    EXPECT_TRUE(testVector0.isSubsetOf(stlUnordederSet));
    EXPECT_FALSE(testVector1.isSubsetOf(stlUnordederSet));

    const auto ycSet = ycstl::YcSet<int> {100, 10, 11, 12, 20};
    EXPECT_FALSE(testVector0.isSubsetOf(ycSet));
    EXPECT_TRUE(testVector1.isSubsetOf(ycSet));
}
