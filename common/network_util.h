#pragma once

#include <string>

class NetworkUtil {
public:
    static std::string get_server_addr();
private:
    static std::string get_hostname();
};
