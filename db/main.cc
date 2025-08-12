#include "server.h"

#include <spdlog/cfg/env.h>

#include "db.h"
#include "db_util.h"

int main(int argc, char **argv) {
    spdlog::cfg::load_env_levels();

    DbUtil::register_node();

    DbImpl service;
    RunServer(&service);

    return 0;
}
