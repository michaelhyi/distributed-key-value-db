#include <string>
#include <memory>
#include <spdlog/spdlog.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/impl/service_type.h>

using grpc::Server;
using grpc::ServerBuilder;

template <typename... Services>
void RunServer(unsigned int port, Services*... services) {
    (static_cast<grpc::Service*>(services), ...); 

    std::string server_address = "0.0.0.0:" + std::to_string(port);

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    (builder.RegisterService(services), ...);
    std::unique_ptr<Server> server(builder.BuildAndStart());

    spdlog::info("Server listening on {}", server_address);
    server->Wait();
}
