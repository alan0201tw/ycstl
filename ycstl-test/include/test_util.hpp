#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Ref: https://github.com/google/googletest/blob/main/googletest/include/gtest/gtest.h
#define EXPECT_THROW_WITH_INFO(statement, expected_exception, expected_substr) \
    EXPECT_THROW(                                                              \
        {                                                                      \
            try {                                                              \
                statement;                                                     \
            } catch (const expected_exception& e) {                            \
                EXPECT_THAT(e.what(), ::testing::HasSubstr(expected_substr));  \
                throw;                                                         \
            } catch (const std::exception& e) {                                \
                FAIL() << "Caught unexpected exception: " << e.what();         \
            }                                                                  \
        },                                                                     \
        expected_exception)
