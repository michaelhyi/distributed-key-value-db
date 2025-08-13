#pragma once

#include <memory>
#include <string>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>

#include "db.grpc.pb.h"

class Shard {
private:
    std::unique_ptr<db::Db::Stub> _stub;

public:
    Shard(std::shared_ptr<grpc::Channel> channel) : _stub(db::Db::NewStub(channel)) {}

    grpc::Status Get(const db::GetRequest *request, db::GetResponse *response) const;
    grpc::Status Set(const db::SetRequest *request, google::protobuf::Empty *response) const;
    grpc::Status Del(const db::DelRequest *request, google::protobuf::Empty *response) const;
};
