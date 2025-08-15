#pragma once

#include <string>

class StringUtil {
public:
    static bool valid_string(const std::string& s);

private:
    static bool blank_string(const std::string& s);
};
