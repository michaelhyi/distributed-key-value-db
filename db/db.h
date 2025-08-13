#pragma once

#include <string>
#include <shared_mutex>
#include <unordered_map>
#include <grpc/grpc.h>
#include <grpcpp/server_context.h>

#include "db.grpc.pb.h"

class DbImpl final : public db::Db::Service {
private:
    std::shared_mutex db_mutex;
    std::unordered_map<std::string, std::string> db;

public:
    grpc::Status Get(grpc::ServerContext *context, const db::GetRequest *request, db::GetResponse *response) override;
    grpc::Status Set(grpc::ServerContext *context, const db::SetRequest *request, google::protobuf::Empty *response) override;
    grpc::Status Del(grpc::ServerContext *context, const db::DelRequest *request, google::protobuf::Empty *response) override;
};
