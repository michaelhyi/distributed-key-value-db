#pragma once

#include <string>

class Util {
public:
    static bool valid_string(const std::string& s);
private:
    static bool string_is_whitespace(const std::string& s);
};
