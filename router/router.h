#pragma once

#include <grpc/grpc.h>
#include <grpcpp/server_context.h>
#include <shared_mutex>
#include <string>
#include <unordered_set>

#include "router.grpc.pb.h"

class RouterImpl final : public router::Router::Service {
private:
    std::unordered_set<std::string> nodes;
    std::shared_mutex nodes_mutex;

public:
    grpc::Status RegisterNode(grpc::ServerContext *context, const router::RegisterNodeRequest *request, google::protobuf::Empty *response) override;
};
