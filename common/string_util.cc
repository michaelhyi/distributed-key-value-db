#include "string_util.h"

#include <cctype>
#include <algorithm>

bool StringUtil::valid_string(const std::string &s) {
    return !s.empty() && !blank_string(s);
}

bool StringUtil::blank_string(const std::string &s) {
    for (char c : s) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            return false;
        }
    }

    return true;
}
