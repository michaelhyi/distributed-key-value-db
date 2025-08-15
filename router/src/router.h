#pragma once

#include <shared_mutex>

#include <grpc/grpc.h>
#include <grpcpp/server_context.h>

#include "shard_discovery.h"
#include "router.grpc.pb.h"

class RouterImpl final : public router::Router::Service {
private:
    ShardDiscoveryService& shard_discovery_service;
    std::shared_mutex shard_discovery_service_mutex;

public:
    RouterImpl(ShardDiscoveryService& shard_discovery_service) : shard_discovery_service(shard_discovery_service) {}
    grpc::Status RegisterNode(grpc::ServerContext *context, const router::RegisterNodeRequest *request, google::protobuf::Empty *response) override;
};
