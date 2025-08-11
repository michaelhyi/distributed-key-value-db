#include "server.h"

#include <string>
#include <memory>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <spdlog/spdlog.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::Service;

void RunServer(Service *service, int port) {
    std::string server_address = "0.0.0.0" + std::to_string(port);

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(service);
    std::unique_ptr<Server> server(builder.BuildAndStart());

    spdlog::info("Server listening on {}", server_address);
    server->Wait();
}
