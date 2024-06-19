
#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include "test_util.hpp"
#include "ycstl.hpp"

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
