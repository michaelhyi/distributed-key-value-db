#pragma once

#include <grpc/grpc.h>
#include <grpcpp/server_context.h>
#include <shared_mutex>
#include <string>
#include <unordered_set>

#include "dkvdb_router.grpc.pb.h"

class DkvdbRouterImpl final : public dkvdb_router::DkvdbRouter::Service {
private:
    std::unordered_set<std::string> nodes;
    std::shared_mutex nodes_mutex;

public:
    grpc::Status RegisterNode(grpc::ServerContext *context, const dkvdb_router::RegisterNodeRequest *request, google::protobuf::Empty *response) override;
};
