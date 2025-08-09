#include "server.h"

#include <string>
#include <memory>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <spdlog/spdlog.h>

#include "dkvdb.h"

using grpc::Server;
using grpc::ServerBuilder;

void RunServer(void) {
    std::string server_address("0.0.0.0:50051");
    DkvdbImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());

    spdlog::info("Server listening on {}", server_address);
    server->Wait();
}
