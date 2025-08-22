#pragma once

#include "zookeeper.h"

class DbUtil {
private:
    ZookeeperService& zookeeper_service;
public:
    DbUtil(ZookeeperService& zookeeper_service) : zookeeper_service(zookeeper_service) {} 
    void register_shard();
};
