#include "server.h"

#include <spdlog/cfg/env.h>

#include "router.h"

int main(int argc, char **argv) {
    spdlog::cfg::load_env_levels();

    RouterImpl service;
    RunServer(&service);

    return 0;
}
