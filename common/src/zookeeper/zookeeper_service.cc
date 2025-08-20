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
        throw std::runtime_error("Failed to create znode");
    }
}
