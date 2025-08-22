#include "server.h"

#include <spdlog/cfg/env.h>

#include "db.h"
#include "db_util.h"

const int GRPC_SERVER_PORT = 50051;

int main(int argc, char **argv) {
    spdlog::cfg::load_env_levels();

    ZookeeperService zookeeper_service("zookeeper:2181");
    DbUtil db_util(zookeeper_service);
    db_util.register_shard();

    DbImpl service;
    RunServer(GRPC_SERVER_PORT, &service);

    return 0;
}
