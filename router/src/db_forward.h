#pragma once

#include <grpc/grpc.h>
#include <grpcpp/server_context.h>

#include "db.grpc.pb.h"
#include "shard_discovery.h"

class DbForwardService : public db::Db::Service {
private:
    const ShardDiscoveryService& shard_discovery_service;

public:
    DbForwardService(const ShardDiscoveryService& shard_discovery_service) : shard_discovery_service(shard_discovery_service) {}

    grpc::Status Get(grpc::ServerContext *context, const db::GetRequest *request, db::GetResponse *response) override;
    grpc::Status Set(grpc::ServerContext *context, const db::SetRequest *request, google::protobuf::Empty *response) override;
    grpc::Status Del(grpc::ServerContext *context, const db::DelRequest *request, google::protobuf::Empty *response) override;
};