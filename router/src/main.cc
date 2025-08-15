#include "server.h"

#include <spdlog/cfg/env.h>

#include "router.h"
#include "db_forward.h"
#include "shard_discovery.h"

const int GRPC_SERVER_PORT = 50051;

int main(int argc, char **argv) {
    spdlog::cfg::load_env_levels();

    ShardDiscoveryService shard_discovery_service;
    DbForwardService db_forward_service(shard_discovery_service);
    RouterImpl router_service(shard_discovery_service);

    RunServer(GRPC_SERVER_PORT, &db_forward_service, &router_service);
    return 0;
}
