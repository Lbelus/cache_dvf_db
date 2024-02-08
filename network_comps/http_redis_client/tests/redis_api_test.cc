#include <gtest/gtest.h>
#include <my_tests.hpp>

// Demonstrate some basic assertions.
TEST(RedisAPITest, BasicRedisAssertions)
{
    // Expect two strings to be equal.
    EXPECT_STREQ(googletest_simple_query("key00", "value00"), "value00");
    // Expect two strings not to be equal.
    EXPECT_STRNE(googletest_simple_query("key01", "value01"), "value00");
    const char json_str[] = "{\"answer\":{\"everything\":42},\"happy\":true,\"list\":[1,0,2],\"name\":\"Niels\",\"nothing\":null,\"object\":{\"currency\":\"USD\",\"value\":42.99},\"pi\":3.141}";
    EXPECT_EQ(googletest_json(json_str), 1);
}

TEST(RedisAPITest, BasicJsonAssertions)
{
    const char json_str[] = "{\"answer\":{\"everything\":42},\"happy\":true,\"list\":[1,0,2],\"name\":\"Niels\",\"nothing\":null,\"object\":{\"currency\":\"USD\",\"value\":42.99},\"pi\":3.141}";
    // Expect values to be equal.
    EXPECT_EQ(googletest_json(json_str), 1);
}

TEST(RedisAPITest, messagePackAssertions)
{
    const char json_str[] = "{\"answer\":{\"everything\":42},\"happy\":true,\"list\":[1,0,2],\"name\":\"Niels\",\"nothing\":null,\"object\":{\"currency\":\"USD\",\"value\":42.99},\"pi\":3.141}";
    // Expect values to be equal.
    EXPECT_EQ(googletest_json(json_str), 1);
}