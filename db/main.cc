#include "server.h"

#include <spdlog/cfg/env.h>

#include "db.h"

int main(int argc, char** argv) {
    spdlog::cfg::load_env_levels();

    DbImpl service;
    RunServer(&service);

    return 0;
}
