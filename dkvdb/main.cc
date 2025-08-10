#include "server.h"

#include <spdlog/cfg/env.h>

int main(int argc, char** argv) {
    spdlog::cfg::load_env_levels();

    RunServer();
    return 0;
}
