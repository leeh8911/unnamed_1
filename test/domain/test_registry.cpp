#include <gtest/gtest.h>

#include "domain/config.h"
#include "domain/registry.h"

class IMyClass
{
   public:
    virtual ~IMyClass() = default;
    virtual std::string string() const = 0;
};
class MyClassA : public IMyClass
{
   public:
    MyClassA(const Kwargs& kwargs)
    {
        name_ = kwargs["name"].as<std::string>();
    }
    std::string string() const override
    {
        return name_;
    }
    std::string name_;
};

class MyClassB : public IMyClass
{
   public:
    MyClassB(const Kwargs& kwargs)
    {
        value_ = kwargs["value"].as<int>();
    }
    std::string string() const override
    {
        return std::to_string(value_);
    }
    int value_;
};

DEFINE_REGISTRY(MY_REGISTRY, IMyClass);
REGISTER(MY_REGISTRY, MyClassA);
REGISTER(MY_REGISTRY, MyClassB);

TEST(Registry, BuildAnyClass)
{
    {
        auto kwargs = Config::parseFromJsonString(R"({"type": "MyClassA", "name": "Alice"})");
        auto ptr = MY_REGISTRY.build(kwargs);
        ASSERT_EQ(ptr->string(), "Alice");
    }

    {
        auto kwargs = Config::parseFromJsonString(R"({"type": "MyClassB", "value": 42})");
        auto ptr = MY_REGISTRY.build(kwargs);
        ASSERT_EQ(ptr->string(), "42");
    }
}
