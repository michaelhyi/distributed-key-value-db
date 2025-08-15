#include "router_client.h"

#include <stdlib.h>
#include <stdexcept>
#include <spdlog/spdlog.h>
#include <grpcpp/client_context.h>

#include "router.grpc.pb.h"

using grpc::Status;
using grpc::StatusCode;
using grpc::ClientContext;
using google::protobuf::Empty;
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
