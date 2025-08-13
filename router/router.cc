#include "router.h"

#include <spdlog/spdlog.h>

#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "shard.h"
#include "string_util.h"

using grpc::Status;
using grpc::StatusCode;
using grpc::ServerContext;
using router::RegisterNodeRequest;
using google::protobuf::Empty;

Status RouterImpl::RegisterNode(ServerContext *context, const RegisterNodeRequest *request, Empty *response) {
    if (!context || !request || !response) {
        return Status(StatusCode::INTERNAL, "There was an error processing your request");
    }

    spdlog::debug("Registering node {}", request->server_address());

    if (!StringUtil::valid_string(request->server_address())) {
        return Status(StatusCode::INVALID_ARGUMENT, "Server address must be non-empty");
    }

    std::shared_ptr<const Shard> shard(
        new Shard(
            grpc::CreateChannel(request->server_address() + ":50051", grpc::InsecureChannelCredentials())
        )
    );

    std::unique_lock lock(shard_discovery_service_mutex);
    shard_discovery_service.add(shard);
    return Status::OK;
}
