#pragma once

#include <memory>
#include <string>

#include "shard.h"
#include "zookeeper_service.h"

class ShardDiscoveryService {
private:
    ZookeeperService& zookeeper_service;

public:
    ShardDiscoveryService(ZookeeperService& zookeeper_service) : zookeeper_service(zookeeper_service) {}
    std::shared_ptr<const Shard> get_shard(const std::string& key) const;
};
