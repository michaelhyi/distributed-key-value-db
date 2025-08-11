#include "server.h"

#include <spdlog/cfg/env.h>

#include "dkvdb.h"

int main(int argc, char** argv) {
    spdlog::cfg::load_env_levels();

    DkvdbImpl service;
    RunServer(&service);

    return 0;
}
