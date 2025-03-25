#include "parser/config_parser.h"

#include <yaml-cpp/yaml.h>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "kwargs.h"

nlohmann::json convertYamlToJson(const YAML::Node& node)
{
    using json = nlohmann::json;

    if (node.IsScalar())
    {
        std::string val = node.Scalar();

        // 타입 추정
        if (val == "true") return true;
        if (val == "false") return false;

        try
        {
            // 정수형
            size_t pos = 0;
            int64_t i = std::stoll(val, &pos);
            if (pos == val.size()) return i;
        }
        catch (...)
        {
        }

        try
        {
            // 실수형
            size_t pos = 0;
            double d = std::stod(val, &pos);
            if (pos == val.size()) return d;
        }
        catch (...)
        {
        }

        return val;  // 문자열 그대로 반환
    }

    if (node.IsSequence())
    {
        json arr = json::array();
        for (const auto& item : node)
        {
            arr.push_back(convertYamlToJson(item));
        }
        return arr;
    }

    if (node.IsMap())
    {
        json obj;
        for (const auto& kv : node)
        {
            obj[kv.first.as<std::string>()] = convertYamlToJson(kv.second);
        }
        return obj;
    }

    return nullptr;
}

Kwargs JsonParser::parse(const std::string& filepath) const
{
    std::ifstream ifs(filepath);
    if (!ifs.is_open()) throw std::runtime_error("Could not open file: " + filepath);

    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return parseFromString(buffer.str());
}

Kwargs JsonParser::parseFromString(const std::string& json_str) const
{
    auto json_obj = nlohmann::json::parse(json_str);
    return Kwargs(json_obj);
}

Kwargs YamlParser::parse(const std::string& filepath) const
{
    std::ifstream ifs(filepath);
    if (!ifs.is_open()) throw std::runtime_error("Could not open file: " + filepath);

    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return parseFromString(buffer.str());
}

Kwargs YamlParser::parseFromString(const std::string& yaml_str) const
{
    auto yaml_obj = YAML::Load(yaml_str);
    auto json_obj = convertYamlToJson(yaml_obj);
    return Kwargs(json_obj);
}

Kwargs XmlParser::parse(const std::string& filepath) const
{
    throw std::runtime_error("Not implemented yet");
}

Kwargs XmlParser::parseFromString(const std::string& xml_str) const
{
    throw std::runtime_error("Not implemented yet");
}
