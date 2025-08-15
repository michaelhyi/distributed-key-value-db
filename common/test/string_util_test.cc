#include "string_util.h"

#include <gtest/gtest.h>

TEST(StringUtilTest, TestValidStringReturnsFalseWhenEmpty) {
    EXPECT_FALSE(StringUtil::valid_string(""));
}

TEST(StringUtilTest, TestValidStringReturnsFalseWhenBlank) {
    EXPECT_FALSE(StringUtil::valid_string(" "));
}

TEST(StringUtilTest, TestValidStringReturnsTrue) {
    EXPECT_TRUE(StringUtil::valid_string("Hello, World!"));
}
