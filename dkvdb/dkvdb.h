#pragma once

#include <grpc/grpc.h>
#include <grpcpp/server_context.h>
#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "dkvdb.grpc.pb.h"

using dkvdb::DelRequest;
using dkvdb::Dkvdb;
using dkvdb::GetRequest;
using dkvdb::GetResponse;
using dkvdb::SetRequest;
using google::protobuf::Empty;
using grpc::ServerContext;
using grpc::Status;

class DkvdbImpl final : public Dkvdb::Service {
  private:
    std::unordered_map<std::string, std::string> db;
    std::shared_mutex db_mutex;

  public:
    Status Get(ServerContext *context, const GetRequest *request,
               GetResponse *response) override;
    Status Set(ServerContext *context, const SetRequest *request,
               Empty *response) override;
    Status Del(ServerContext *context, const DelRequest *request,
               Empty *response) override;
};
