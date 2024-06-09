
#include <gtest/gtest.h>

#include <set>
#include <unordered_set>

#include "ycstl.hpp"

TEST(set, basic) {
    auto testSet = ycstl::YcSet<int> {};
    EXPECT_TRUE(testSet.isSorted());
    EXPECT_TRUE(testSet.isUnique());
}

TEST(set, isSubsetOf) {
    const auto testSet0 = ycstl::YcSet<int> {0, 1, 2};
    const auto testSet1 = ycstl::YcSet<int> {0, 1, 2, 3, 4};
    EXPECT_TRUE(testSet0.isSubsetOf(testSet1));
    EXPECT_FALSE(testSet1.isSubsetOf(testSet0));

    const auto testSet2 = ycstl::YcSet<int> {10, 11, 12};
    const auto testSet3 = ycstl::YcSet<int> {20, 21, 22, 23, 24};
    EXPECT_TRUE(testSet2.isSubsetOf(testSet2));
    EXPECT_TRUE(testSet3.isSubsetOf(testSet3));
    EXPECT_FALSE(testSet2.isSubsetOf(testSet3));
    EXPECT_FALSE(testSet3.isSubsetOf(testSet2));

    const auto stlSet = std::set<int> {10, 11, 12, 20, 21, 22, 23, 24};
    EXPECT_FALSE(testSet0.isSubsetOf(stlSet));
    EXPECT_TRUE(testSet2.isSubsetOf(stlSet));

    const auto stlUnordederSet = std::unordered_set<int> {0, 1, 2, 3, 4, 5};
    EXPECT_TRUE(testSet0.isSubsetOf(stlUnordederSet));
    EXPECT_TRUE(testSet1.isSubsetOf(stlUnordederSet));
    EXPECT_FALSE(testSet2.isSubsetOf(stlUnordederSet));
}
