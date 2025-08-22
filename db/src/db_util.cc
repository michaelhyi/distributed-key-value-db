#include "db_util.h"

#include <chrono>
#include <string>
#include <thread>
#include <stdexcept>
#include <spdlog/spdlog.h>

#include "network_util.h"
#include "zookeeper.h"

const int MAX_RETRIES = 5;
const int RETRY_DELAY_MS = 2000;

void DbUtil::register_shard() {
    std::string server_address = NetworkUtil::get_server_address();

    try {
        zookeeper_service.create_znode("/shards", server_address, ZOO_PERSISTENT);
    } catch (const std::exception& e) {
    }

    bool registered = false;
    for (int i = 0; i < MAX_RETRIES; i++) {
        try {
            zookeeper_service.create_znode("/shards/" + NetworkUtil::get_hostname(), server_address, ZOO_EPHEMERAL);
            registered = true;
            break;
        } catch (const std::exception& e) {
            spdlog::warn("{}", e.what());
            std::this_thread::sleep_for(std::chrono::milliseconds(RETRY_DELAY_MS));
        }
    }

    if (!registered) {
        throw std::runtime_error("Failed to register node");
    }
}
