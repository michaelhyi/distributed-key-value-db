#include "dkvdb_router.h"

#include <spdlog/spdlog.h>

#include "util.h"

using dkvdb_router::RegisterNodeRequest;
using google::protobuf::Empty;
using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;

Status DkvdbRouterImpl::RegisterNode(ServerContext *context, const RegisterNodeRequest *request, Empty *response) {
    if (!context || !request || !response) {
        return Status(StatusCode::INTERNAL, "There was an error processing your request");
    }

    spdlog::debug("Registering node with server_addres={}", request->server_address());

    if (!Util::valid_string(request->server_address())) {
        return Status(StatusCode::INVALID_ARGUMENT, "Server address must be non-empty");
    }

    std::shared_lock lock(nodes_mutex);
    nodes.insert(request->server_address());
    return Status::OK;
}
