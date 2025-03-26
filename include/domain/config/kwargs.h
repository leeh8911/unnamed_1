#ifndef __KWARGS_HPP__
#define __KWARGS_HPP__

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

class Kwargs
{
   public:
    Kwargs() = default;
    explicit Kwargs(const nlohmann::json& data) : data_(data) {}

    // 하위 접근 지원 (kwargs["sub"]["name"])
    Kwargs operator[](const std::string& key) const
    {
        if (!data_.contains(key))
        {
            throw std::runtime_error("Key not found: " + key);
        }
        return Kwargs(data_.at(key));
    }

    // 리스트 인덱싱 지원 (kwargs["list"][0])
    Kwargs operator[](size_t idx) const
    {
        if (!data_.is_array())
        {
            throw std::runtime_error("Data is not an array");
        }
        if (idx >= data_.size())
        {
            throw std::out_of_range("Index out of range");
        }
        return Kwargs(data_.at(idx));
    }

    // 값 추출 (kwargs["name"].as<std::string>())
    template <typename T>
    T as() const
    {
        return data_.get<T>();
    }

    // 키 존재 여부 확인
    bool has(const std::string& key) const
    {
        return data_.contains(key);
    }

    // 내부 데이터 접근 (디버깅용)
    const nlohmann::json& raw() const
    {
        return data_;
    }

   private:
    nlohmann::json data_;
};

#endif  // __KWARGS_HPP__