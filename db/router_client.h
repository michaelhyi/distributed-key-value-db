#pragma once

#include <memory>
#include <string>
#include <grpcpp/channel.h>

#include "router.grpc.pb.h"

class RouterClient {
private:
    std::unique_ptr<router::Router::Stub> _stub;

public:
    RouterClient(std::shared_ptr<grpc::Channel> channel) : _stub(router::Router::NewStub(channel)) {}
    void RegisterNode(const std::string &server_address);
};
