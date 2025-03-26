#include <gtest/gtest.h>

#include <string>

#include "domain/config.h"

TEST(Config, HandleJsonConfigCase)
{
    // json 형식의 문자열을 만들어서 config 객체를 생성한다.

    std::string config_str = R"(
        {
            "name": "test",
            "value": 100,
            "sub": {
                "name": "subtest",
                "value": 200
            },
            "list": [1, 2, 3, 4]
            
        }
    )";

    auto kwargs = JsonParser().parseFromString(config_str);

    EXPECT_EQ(kwargs["name"].as<std::string>(), "test");
    EXPECT_EQ(kwargs["value"].as<int64_t>(), 100);
    EXPECT_EQ(kwargs["sub"]["name"].as<std::string>(), "subtest");
    EXPECT_EQ(kwargs["sub"]["value"].as<int64_t>(), 200);
    EXPECT_EQ(kwargs["list"][0].as<int64_t>(), 1);
    EXPECT_EQ(kwargs["list"][1].as<int64_t>(), 2);
    EXPECT_EQ(kwargs["list"][2].as<int64_t>(), 3);
    EXPECT_EQ(kwargs["list"][3].as<int64_t>(), 4);
}

TEST(Config, HandleYamlConfigCase)
{
    // yaml 형식의 문자열을 만들어서 config 객체를 생성한다.

    std::string config_str = R"(
name: test
value: 100
sub:
  name: subtest
  value: 200
list:
  - 1
  - 2
  - 3
  - 4
)";

    auto kwargs = YamlParser().parseFromString(config_str);

    EXPECT_EQ(kwargs["name"].as<std::string>(), "test");
    EXPECT_EQ(kwargs["value"].as<int64_t>(), 100);
    EXPECT_EQ(kwargs["sub"]["name"].as<std::string>(), "subtest");
    EXPECT_EQ(kwargs["sub"]["value"].as<int64_t>(), 200);
    EXPECT_EQ(kwargs["list"][0].as<int64_t>(), 1);
    EXPECT_EQ(kwargs["list"][1].as<int64_t>(), 2);
    EXPECT_EQ(kwargs["list"][2].as<int64_t>(), 3);
    EXPECT_EQ(kwargs["list"][3].as<int64_t>(), 4);
}