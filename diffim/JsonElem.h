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

    std::string to_string();
    std::string to_pritty_string(int padding);

private:
    std::string _title;
    DataType _type{DataType::Object};
    std::optional<std::string> _value;
    std::vector<JsonElem> _children;
    
    std::string get_value();
    std::string get_value_pritty(int padding);
    std::string get_container_values();
    std::string get_container_values_pritty(int padding=0);

    std::string end_delimiter();
    std::string start_delimiter();

    std::string quote(const string status);
    std::string escape_chars(const string text);

};
