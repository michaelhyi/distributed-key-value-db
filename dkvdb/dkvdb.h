#pragma once

#include <grpc/grpc.h>
#include <grpcpp/server_context.h>
#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "dkvdb.grpc.pb.h"

class DkvdbImpl final : public dkvdb::Dkvdb::Service {
private:
    std::unordered_map<std::string, std::string> db;
    std::shared_mutex db_mutex;

public:
    grpc::Status Get(grpc::ServerContext *context, const dkvdb::GetRequest *request, dkvdb::GetResponse *response) override;
    grpc::Status Set(grpc::ServerContext *context, const dkvdb::SetRequest *request, google::protobuf::Empty *response) override;
    grpc::Status Del(grpc::ServerContext *context, const dkvdb::DelRequest *request, google::protobuf::Empty *response) override;
};
