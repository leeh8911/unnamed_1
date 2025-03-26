#ifndef __REGISTRY_H__
#define __REGISTRY_H__

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "domain/config.h"

class GenericRegistry
{
   public:
    using Creator = std::function<std::shared_ptr<void>(const Kwargs&)>;

    void register_class(const std::string& name, Creator creator)
    {
        if (creators_.count(name))
        {
            throw std::runtime_error("Class already registered: " + name);
        }
        creators_[name] = std::move(creator);
    }

    std::shared_ptr<void> build(const std::string& name, const Kwargs& kwargs) const
    {
        auto it = creators_.find(name);
        if (it == creators_.end())
        {
            throw std::runtime_error("Unknown class: " + name);
        }
        return it->second(kwargs);
    }

    std::shared_ptr<void> build(const Kwargs& kwargs) const
    {
        return build(kwargs["type"].as<std::string>(), kwargs);
    }

   private:
    std::unordered_map<std::string, Creator> creators_;
};

// 네임스페이스별로 Registry 인스턴스를 생성
#define DEFINE_REGISTRY(NS)            \
    namespace NS                       \
    {                                  \
    inline GenericRegistry& Registry() \
    {                                  \
        static GenericRegistry inst;   \
        return inst;                   \
    }                                  \
    }

// 자동 등록 매크로
#define REGISTER(NS, ClassType)                                                             \
    namespace                                                                               \
    {                                                                                       \
    struct AutoRegister_##ClassType                                                         \
    {                                                                                       \
        AutoRegister_##ClassType()                                                          \
        {                                                                                   \
            NS::Registry().register_class(#ClassType,                                       \
                                          [](const Kwargs& kwargs) -> std::shared_ptr<void> \
                                          { return std::make_shared<ClassType>(kwargs); }); \
        }                                                                                   \
    };                                                                                      \
    static AutoRegister_##ClassType global_auto_##ClassType;                                \
    }

#endif  // __REGISTRY_H__
