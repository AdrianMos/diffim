#include "JsonElem.h"
#include <algorithm>
#include <sstream>
#include <utility>

using std::string;

JsonElem::JsonElem()
{
}

JsonElem::JsonElem(std::string title, std::string value)
    : _title(title), _value(value), _type{DataType::String}
{
}

JsonElem::JsonElem(std::string title, int value)
    : _title(title), _value(std::to_string(value)), _type{DataType::Integer}
{
}

JsonElem::JsonElem(std::string title) : _title(title)
{
}

JsonElem::JsonElem(std::string title, DataType dataType) : JsonElem(title)
{
    _type = dataType;
}


JsonElem::JsonElem(std::string title, std::initializer_list<JsonElem> l)
    : _title(title), _children(l)
{
}

JsonElem::JsonElem(std::string title, std::vector<JsonElem> elements)
    : _title(title), _children(elements)
{
}


JsonElem& JsonElem::add(JsonElem elem)
{
    _children.push_back(elem);
    return *this;
}


std::string JsonElem::to_string() const
{
    if (!_title.empty())
        return quote(_title) + ": " + get_value();
    return get_value();
}

std::string JsonElem::to_pritty_string(int padding) const
{
    if (!_title.empty())
        return std::string(padding, ' ') + quote(_title) + ": "
               + get_value_pritty(padding);

    return get_value_pritty(padding);
}


std::string JsonElem::get_value() const
{
    switch (_type) {
        case DataType::Integer: return _value.value();
        case DataType::String: return quote(escape_chars(_value.value()));
        case DataType::List:
        case DataType::Object: return get_container_values();
        default: return "";
    }
}


std::string JsonElem::get_value_pritty(int padding) const
{
    switch (_type) {
        case DataType::Integer: return _value.value();
        case DataType::String: return quote(escape_chars(_value.value()));
        case DataType::List:
        case DataType::Object: return get_container_values_pritty(padding);
        default: return "";
    }
}

std::string JsonElem::get_container_values() const
{
    std::ostringstream oss;
    oss << start_delimiter();

    bool first = true;
    for (auto& child : _children) {
        if (!first)
            oss << ", ";
        oss << child.to_string();
        first = false;
    }

    oss << end_delimiter();
    return oss.str();
}

std::string JsonElem::get_container_values_pritty(int padding) const
{
    std::ostringstream oss;
    std::string pad(padding, ' ');
    oss << pad << start_delimiter();

    bool first = true;
    for (auto& child : _children) {
        if (!first)
            oss << ", ";
        oss << "\n" << child.to_pritty_string(padding + 2);
        first = false;
    }

    oss << pad << end_delimiter();
    return oss.str();
}


std::string JsonElem::end_delimiter() const
{
    switch (_type) {
        case DataType::Object: return "}";
        case DataType::List: return "]";
        default: return "";
    }
}

std::string JsonElem::start_delimiter() const
{
    switch (_type) {
        case DataType::Object: return "{";
        case DataType::List: return "[";
        default: return "";
    }
}


string JsonElem::quote(const string status) const
{
    return "\"" + status + "\"";
}


string JsonElem::escape_chars(const string text) const
{
    std::string escaped_text{text};
    std::replace(escaped_text.begin(), escaped_text.end(), '\\', '/');
    return escaped_text;
}
