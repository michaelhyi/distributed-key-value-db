#pragma once
#define THREADED 1

#include <string>
#include <zookeeper/zookeeper.h>

class ZookeeperService {
private:
    bool connected;
    bool expired;
    zhandle_t *zk_handler;

    static void watcher(zhandle_t *zkH, int type, int state, const char *path, void *watcherCtx);

public:
    ZookeeperService(const std::string& host);
    ~ZookeeperService();
    ZookeeperService(const ZookeeperService& other) = delete;
    ZookeeperService& operator=(const ZookeeperService& other) = delete;
    ZookeeperService(ZookeeperService&& other);
    ZookeeperService& operator=(ZookeeperService&& other);

    void create_znode(const std::string& path, const std::string& data, int flags = ZOO_EPHEMERAL);
};
