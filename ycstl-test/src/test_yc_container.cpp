
#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include "test_util.hpp"
#include "ycstl.hpp"

TEST(TestYcContainer, getSetUnion) {
    auto testVector0 = ycstl::YcVector<int> {1, 2, 3, 4, 5, 6, 7};
    EXPECT_FALSE(testVector0.isSorted());
    auto testVector1 = ycstl::YcVector<int> {5, 6, 7, 8, 9, 10, 21, 22};
    EXPECT_FALSE(testVector1.isSorted());

    using OutputContainer = std::vector<int>;
    EXPECT_THROW_WITH_INFO(testVector0.getSetUnion<OutputContainer>(testVector1), ycstl::exception::YcException,
                           "Current container is not sorted");
    testVector0.sort();
    EXPECT_THROW_WITH_INFO(testVector0.getSetUnion<OutputContainer>(testVector1), ycstl::exception::YcException,
                           "Rhs container is not sorted");
    testVector1.sort();

    const auto setUnion = testVector0.getSetUnion<OutputContainer>(testVector1);
    const auto expectedAnswer = OutputContainer {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 21, 22};
    EXPECT_EQ(setUnion, expectedAnswer);
}

TEST(TestYcContainer, getSetIntersection) {
    auto testVector0 = ycstl::YcVector<int> {1, 2, 3, 4, 5, 6, 7};
    EXPECT_FALSE(testVector0.isSorted());
    auto testVector1 = ycstl::YcVector<int> {5, 6, 7, 8, 9, 10, 21, 22};
    EXPECT_FALSE(testVector1.isSorted());

    using OutputContainer = std::vector<int>;
    EXPECT_THROW_WITH_INFO(testVector0.getSetIntersection<OutputContainer>(testVector1), ycstl::exception::YcException,
                           "Current container is not sorted");
    testVector0.sort();
    EXPECT_THROW_WITH_INFO(testVector0.getSetIntersection<OutputContainer>(testVector1), ycstl::exception::YcException,
                           "Rhs container is not sorted");
    testVector1.sort();

    const auto setIntersection = testVector0.getSetIntersection<OutputContainer>(testVector1);
    const auto expectedAnswer = OutputContainer {5, 6, 7};
    EXPECT_EQ(setIntersection, expectedAnswer);
}

TEST(TestYcContainer, getSetDifference) {
    auto testVector0 = ycstl::YcVector<int> {1, 2, 3, 4, 5, 6, 7};
    EXPECT_FALSE(testVector0.isSorted());
    auto testVector1 = ycstl::YcVector<int> {5, 6, 7, 8, 9, 10, 21, 22};
    EXPECT_FALSE(testVector1.isSorted());

    using OutputContainer = std::vector<int>;
    EXPECT_THROW_WITH_INFO(testVector0.getSetDifference<OutputContainer>(testVector1), ycstl::exception::YcException,
                           "Current container is not sorted");
    testVector0.sort();
    EXPECT_THROW_WITH_INFO(testVector0.getSetDifference<OutputContainer>(testVector1), ycstl::exception::YcException,
                           "Rhs container is not sorted");
    testVector1.sort();

    const auto setDifference = testVector0.getSetDifference<OutputContainer>(testVector1);
    const auto expectedAnswer = OutputContainer {1, 2, 3, 4};
    EXPECT_EQ(setDifference, expectedAnswer);
}

TEST(TestYcContainer, getSetSymmetricDifference) {
    auto testVector0 = ycstl::YcVector<int> {1, 2, 3, 4, 5, 6, 7};
    EXPECT_FALSE(testVector0.isSorted());
    auto testVector1 = ycstl::YcVector<int> {5, 6, 7, 8, 9, 10, 21, 22};
    EXPECT_FALSE(testVector1.isSorted());

    using OutputContainer = std::vector<int>;
    EXPECT_THROW_WITH_INFO(testVector0.getSetSymmetricDifference<OutputContainer>(testVector1),
                           ycstl::exception::YcException, "Current container is not sorted");
    testVector0.sort();
    EXPECT_THROW_WITH_INFO(testVector0.getSetSymmetricDifference<OutputContainer>(testVector1),
                           ycstl::exception::YcException, "Rhs container is not sorted");
    testVector1.sort();

    const auto setSymmetricDifference = testVector0.getSetSymmetricDifference<OutputContainer>(testVector1);
    const auto expectedAnswer = OutputContainer {1, 2, 3, 4, 8, 9, 10, 21, 22};
    EXPECT_EQ(setSymmetricDifference, expectedAnswer);
}
