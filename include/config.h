#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <filesystem>
#include <memory>

#include "kwargs.h"
#include "parser/config_parser.h"

namespace Config
{
inline Kwargs load(const std::string& path)
{
    std::filesystem::path p(path);
    std::string ext = p.extension().string();

    std::unique_ptr<IConfigParser> parser;

    if (ext == ".json")
    {
        parser = std::make_unique<JsonParser>();
    }
    else if (ext == ".yaml" || ext == ".yml")
    {
        parser = std::make_unique<YamlParser>();
    }
    else if (ext == ".xml")
    {
        parser = std::make_unique<XmlParser>();
    }
    else
    {
        throw std::runtime_error("Unsupported config format: " + ext);
    }

    return parser->parse(path);
}

inline Kwargs parseFromJsonString(const std::string& json_str)
{
    return JsonParser().parseFromString(json_str);
}

inline Kwargs parseFromYamlString(const std::string& yaml_str)
{
    return YamlParser().parseFromString(yaml_str);
}

inline Kwargs parseFromXmlString(const std::string& xml_str)
{
    return XmlParser().parseFromString(xml_str);
}

}  // namespace Config

#endif  // __CONFIG_H__