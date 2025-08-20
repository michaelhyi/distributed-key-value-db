#include "server.h"

#include <spdlog/cfg/env.h>

#include "db_forward.h"
#include "shard_discovery.h"
#include "zookeeper_service.h"

const int GRPC_SERVER_PORT = 50051;

int main(int argc, char **argv) {
    spdlog::cfg::load_env_levels();

    ZookeeperService zookeeper_service("zookeeper:2181");
    ShardDiscoveryService shard_discovery_service(zookeeper_service);
    DbForwardService db_forward_service(shard_discovery_service);

    RunServer(GRPC_SERVER_PORT, &db_forward_service);
    return 0;
}
