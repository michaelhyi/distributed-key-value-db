#include "network_util.h"

#include <stdexcept>
#include <stdlib.h>
#include <unistd.h>

std::string NetworkUtil::get_server_addr() {
    std::string hostname = get_hostname();
    return hostname + ".db.default.svc.cluster.local";
}

std::string NetworkUtil::get_hostname() {
    char buffer[256];
    int err = gethostname(buffer, 256);

    if (err) {
        throw std::runtime_error("Failed to get hostname");
    }

    buffer[255] = '\0';
    return std::string(buffer);
}
