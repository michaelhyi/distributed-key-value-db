#include "util.h"

#include <cctype>
#include <algorithm>

bool Util::valid_string(const std::string &s) {
    return !s.empty() && !string_is_whitespace(s);
}

bool Util::string_is_whitespace(const std::string &s) {
    return std::all_of(s.begin(), s.end(), [](unsigned char c)
                       { return std::isspace(c); });
}
