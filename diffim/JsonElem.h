#pragma once
#include <string>
#include <vector>
#include <optional>

using std::string;

// Handles grouping and formatting of JSON data.
class JsonElem {
 public:
    enum class DataType { List, Object, String, Integer };

    JsonElem();
    JsonElem(std::string title);
    JsonElem(std::string title, int value);
    JsonElem(std::string title, std::string value);
    JsonElem(std::string title, DataType dataType);
    JsonElem(std::string title, std::initializer_list<JsonElem> l);
    JsonElem(std::string title, std::vector<JsonElem> elements);


    JsonElem& add(JsonElem elem);

    std::string to_string() const;
    std::string to_pritty_string(int padding) const;

private:
    std::string _title;
    DataType _type{DataType::Object};
    std::optional<std::string> _value;
    std::vector<JsonElem> _children;
    
    std::string get_value() const;
    std::string get_value_pritty(int padding) const;
    std::string get_container_values() const;
    std::string get_container_values_pritty(int padding=0) const; 

    std::string end_delimiter() const;
    std::string start_delimiter() const;

    std::string quote(const string status) const;
    std::string escape_chars(const string text) const;

};
