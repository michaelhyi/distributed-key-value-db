#pragma once

#include <grpc/grpc.h>
#include <grpcpp/server_context.h>
#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "db.grpc.pb.h"

class DbImpl final : public db::Db::Service {
private:
    std::unordered_map<std::string, std::string> db;
    std::shared_mutex db_mutex;

public:
    grpc::Status Get(grpc::ServerContext *context, const db::GetRequest *request, db::GetResponse *response) override;
    grpc::Status Set(grpc::ServerContext *context, const db::SetRequest *request, google::protobuf::Empty *response) override;
    grpc::Status Del(grpc::ServerContext *context, const db::DelRequest *request, google::protobuf::Empty *response) override;
};
