
#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <set>
#include <unordered_set>

#include "ycstl.hpp"

TEST(TestYcVector, basic) {
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

TEST(TestYcVector, isSubsetOf) {
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

class Dummy {
public:
    static inline constexpr auto FailureMessage = "No dummy objects should be constructed";

    Dummy() { fail(); }
    Dummy(const int i) {}
    void fail() const { ADD_FAILURE() << FailureMessage; }
};

TEST(TestYcVector, reserve) {
    auto testVector = ycstl::YcVector<Dummy> {};
    EXPECT_NONFATAL_FAILURE(testVector.emplace_back(), Dummy::FailureMessage);
    constexpr auto Capacity = 256u;
    EXPECT_GT(Capacity, testVector.capacity()) << testVector.capacity();
    testVector.reserve(Capacity);
    EXPECT_EQ(Capacity, testVector.capacity());

    while (testVector.size() < Capacity) {
        testVector.emplace_back(0);
    }

    EXPECT_EQ(Capacity, testVector.size());
    EXPECT_NONFATAL_FAILURE(testVector.emplace_back(), Dummy::FailureMessage);
}

TEST(TestYcVector, resize) {
    EXPECT_NONFATAL_FAILURE(std::make_unique<ycstl::YcVector<Dummy>>(1), Dummy::FailureMessage);

    auto testVector1 = ycstl::YcVector<Dummy> {};
    EXPECT_NONFATAL_FAILURE(testVector1.resize(1), Dummy::FailureMessage);
}

TEST(TestYcVector, iterable) {
    const auto testVector0 = ycstl::YcVector<int> {0, 1, 2};
    const auto testVector1 = ycstl::YcVector<int> {10, 11, 12, 20};

    auto testVector2 = ycstl::YcVector<int> {};
    testVector2.reserve(testVector0.size() * testVector1.size());
    for (const auto x : testVector0) {
        for (const auto y : testVector1) {
            testVector2.emplace_back(x * y);
        }
    }
    EXPECT_EQ(testVector0.size() * testVector1.size(), testVector2.size());
}

TEST(TestYcVector, sort) {
    {
        auto testVectorSorted = ycstl::YcVector<int> {10, 11, 12};
        EXPECT_TRUE(std::is_sorted(testVectorSorted.cbegin(), testVectorSorted.cend()));
        EXPECT_FALSE(testVectorSorted.isSorted());

        testVectorSorted.sort();
        EXPECT_TRUE(std::is_sorted(testVectorSorted.cbegin(), testVectorSorted.cend()));
        EXPECT_TRUE(testVectorSorted.isSorted());

        testVectorSorted.emplace_back(100);
        EXPECT_TRUE(std::is_sorted(testVectorSorted.cbegin(), testVectorSorted.cend()));
        EXPECT_FALSE(testVectorSorted.isSorted());
    }
    {
        auto testVector = ycstl::YcVector<int> {210, 101, -12, 997887, -3344};
        EXPECT_FALSE(std::is_sorted(testVector.cbegin(), testVector.cend()));
        EXPECT_FALSE(testVector.isSorted());

        testVector.sort();
        EXPECT_TRUE(std::is_sorted(testVector.cbegin(), testVector.cend()));
        EXPECT_TRUE(testVector.isSorted());

        testVector.emplace_back(100);
        EXPECT_FALSE(std::is_sorted(testVector.cbegin(), testVector.cend()));
        EXPECT_FALSE(testVector.isSorted());
    }
}

TEST(TestYcVector, erase) {
    const auto testVector = ycstl::YcVector<int> {210, 101, -12, 997887, -3344, 0, 1, -3, 7, 32145, 11};
    auto testSortedVector = testVector.getSortedVector();
    EXPECT_TRUE(std::is_sorted(testSortedVector.cbegin(), testSortedVector.cend()));
    EXPECT_TRUE(testSortedVector.isSorted());
    {
        const auto originalSize = testSortedVector.size();
        testSortedVector.erase(testSortedVector.cbegin() + 2);
        EXPECT_EQ(originalSize - 1u, testSortedVector.size());
        EXPECT_TRUE(std::is_sorted(testSortedVector.cbegin(), testSortedVector.cend()));
        EXPECT_TRUE(testSortedVector.isSorted());
    }
    {
        const auto originalSize = testSortedVector.size();
        testSortedVector.erase(testSortedVector.cbegin(), testSortedVector.cbegin() + 2);
        EXPECT_EQ(originalSize - 2u, testSortedVector.size());
        EXPECT_TRUE(std::is_sorted(testSortedVector.cbegin(), testSortedVector.cend()));
        EXPECT_TRUE(testSortedVector.isSorted());
    }
}
