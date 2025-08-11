#include "server.h"

#include <spdlog/cfg/env.h>

#include "dkvdb_router.h"

int main(int argc, char **argv) {
    spdlog::cfg::load_env_levels();

    DkvdbRouterImpl service;
    RunServer(&service);

    return 0;
}
