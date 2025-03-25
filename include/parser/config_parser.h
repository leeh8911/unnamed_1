#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__

#include <memory>
#include <string>

#include "kwargs.h"

class IConfigParser
{
   public:
    virtual ~IConfigParser() = default;
    virtual Kwargs parse(const std::string& filepath) const = 0;
    virtual Kwargs parseFromString(const std::string& str) const = 0;
};

class JsonParser : public IConfigParser
{
   public:
    Kwargs parse(const std::string& filepath) const override;
    Kwargs parseFromString(const std::string& json_str) const override;
};

class YamlParser : public IConfigParser
{
   public:
    Kwargs parse(const std::string& filepath) const override;
    Kwargs parseFromString(const std::string& yaml_str) const override;
};

class XmlParser : public IConfigParser
{
   public:
    Kwargs parse(const std::string& filepath) const override;
    Kwargs parseFromString(const std::string& xml_str) const override;
};

#endif  // __CONFIG_PARSER_H__