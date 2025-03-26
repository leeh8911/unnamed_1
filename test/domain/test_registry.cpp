#include <gtest/gtest.h>

#include "domain/config.h"
#include "domain/registry.h"

DEFINE_REGISTRY(MY_REGISTRY);

class MyClassA
{
   public:
    MyClassA(const Kwargs& kwargs)
    {
        name_ = kwargs["name"].as<std::string>();
    }
    std::string name_;
};

class MyClassB
{
   public:
    MyClassB(const Kwargs& kwargs)
    {
        value_ = kwargs["value"].as<int>();
    }
    int value_;
};

REGISTER(MY_REGISTRY, MyClassA);
REGISTER(MY_REGISTRY, MyClassB);

TEST(Registry, BuildAnyClass)
{
    {
        auto kwargs = Config::parseFromJsonString(R"({"type": "MyClassA", "name": "Alice"})");
        auto ptr = MY_REGISTRY.build(kwargs);
        auto a = std::static_pointer_cast<MyClassA>(ptr);
        ASSERT_EQ(a->name_, "Alice");
    }

    {
        auto kwargs = Config::parseFromJsonString(R"({"type": "MyClassB", "value": 42})");
        auto ptr = MY_REGISTRY.build(kwargs);
        auto b = std::static_pointer_cast<MyClassB>(ptr);
        ASSERT_EQ(b->value_, 42);
    }
}
