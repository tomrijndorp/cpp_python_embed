#include "lib/foo.hpp"

#include <gtest/gtest.h>

TEST(It, Works)
{
    ASSERT_EQ(foo(), 1);
}