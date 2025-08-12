#include "router_client.h"

#include <spdlog/spdlog.h>
#include <grpcpp/client_context.h>
#include <stdexcept>
#include <stdlib.h>

#include "router.grpc.pb.h"

using google::protobuf::Empty;
using grpc::ClientContext;
using grpc::Status;
using grpc::StatusCode;
using router::RegisterNodeRequest;

void RouterClient::RegisterNode(const std::string &server_address) {
    spdlog::debug("Registering node {}", server_address);

    RegisterNodeRequest request;
    request.set_server_address(server_address);

    ClientContext context;
    Empty response;
    Status status = _stub->RegisterNode(&context, request, &response);

    if (!status.ok()) {
        throw std::runtime_error("Failed to register node");
    }
}
