#include "zookeeper_service.h"

#include <unistd.h>
#include <stdexcept>
#include <spdlog/spdlog.h>

void ZookeeperService::watcher(zhandle_t *zkH, int type, int state, const char *path, void *watcherCtx) {
    if (type != ZOO_SESSION_EVENT) {
        return;
    }

    ZookeeperService *service = static_cast<ZookeeperService *>(watcherCtx);

    if (!service) {
        throw std::runtime_error("Cannot use null watcher context");
    }

    if (state == ZOO_CONNECTED_STATE) {
        service->connected = true;
    } else if (state == ZOO_NOTCONNECTED_STATE) {
        service->connected = false;
    } else if (state == ZOO_EXPIRED_SESSION_STATE) {
        service->expired = true;
        service->connected = false;
        zookeeper_close(zkH);
    }
}

ZookeeperService::ZookeeperService(const std::string& host) {
    connected = false;
    expired = false;
    zk_handler = zookeeper_init(host.c_str(), watcher, 100000, nullptr, this, 0);

    if (!zk_handler) {
        throw std::runtime_error("Failed to init zookeeper");
    }
}

ZookeeperService::~ZookeeperService() {
    if (!zk_handler) {
        return;
    }

    zookeeper_close(zk_handler);
}

ZookeeperService::ZookeeperService(ZookeeperService&& other) {
    connected = other.connected;
    expired = other.expired;
    zk_handler = other.zk_handler;

    other.zk_handler = nullptr;
}

ZookeeperService& ZookeeperService::operator=(ZookeeperService&& other) {
    if (&other == this) {
        return *this;
    }

    if (zk_handler) {
        zookeeper_close(zk_handler);
    }

    connected = other.connected;
    expired = other.expired;
    zk_handler = other.zk_handler;

    other.zk_handler = nullptr;
    return *this;
}

void ZookeeperService::create_znode(const std::string& path, const std::string& data, int flags) {
    char path_buf[512];

    int ret = zoo_create(
        zk_handler,
        path.c_str(),
        data.c_str(),
        data.size(),
        &ZOO_OPEN_ACL_UNSAFE,
        flags,
        path_buf,
        sizeof(path_buf) 
    );

    if (ret != ZOK) {
        throw std::runtime_error("Failed to create znode with error code " + ret);
    }
}

std::string ZookeeperService::get_znode(const std::string& path) {
    spdlog::debug("Getting ZooKeeper znode {}", path);

    char buf[512];
    int buf_len = sizeof(buf);
    struct Stat stat;
    int ret = zoo_get(zk_handler, path.c_str(), 0, buf, &buf_len, &stat);

    if (ret != ZOK) {
        spdlog::warn("Erroring getting ZooKeeper znode with error code {}", ret);
        throw std::runtime_error("Failed getting znode with error code " + ret);
    }

    return std::string(buf, buf_len);
}

std::unordered_map<std::string, std::string> ZookeeperService::get_children(const std::string& path) {
    spdlog::info("Getting ZooKeeper children of znode {}", path);

    std::unordered_map<std::string, std::string> znodes;
    struct String_vector strings;
    int ret = zoo_get_children(zk_handler, path.c_str(), 0, &strings);
    // TODO: handle all errors
    if (ret != ZOK) {
        throw std::runtime_error("Failed getting znodes with code " + ret);
    }

    for (int i = 0; i < strings.count; i++) {
        std::string znode = path + "/" + std::string(strings.data[i]);
        spdlog::debug("Getting znode {}", znode);

        std::string data;
        try {
            data = get_znode(znode);
        } catch (const std::exception& e) {
            spdlog::warn("Error getting znode {}: {}", znode, e.what());
        }

        spdlog::debug("Received znode {} with data: {}", znode, data);
        znodes[znode] = data;
    }

    deallocate_String_vector(&strings);
    return znodes;
}
