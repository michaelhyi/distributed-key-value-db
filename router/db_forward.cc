#include "db_forward.h"

#include <memory>
#include <spdlog/spdlog.h>

#include "shard.h"

using db::GetRequest;
using db::GetResponse;
using db::SetRequest;
using db::DelRequest;

using grpc::Status;
using grpc::StatusCode;
using grpc::ServerContext;
using google::protobuf::Empty;

Status DbForwardService::Get(ServerContext *context, const GetRequest *request, GetResponse *response) {
    spdlog::info("Forwarding GetRequest with key={}", request->key());
    std::shared_ptr<const Shard> shard = shard_discovery_service.get_shard(request->key());
    return shard->Get(request, response);
}

Status DbForwardService::Set(ServerContext *context, const SetRequest *request, Empty *response) {
    spdlog::info("Forwarding SetRequest with key={}, value={}", request->key(), request->value());
    std::shared_ptr<const Shard> shard = shard_discovery_service.get_shard(request->key());
    return shard->Set(request, response);
}

Status DbForwardService::Del(ServerContext *context, const DelRequest *request, Empty *response) {
    spdlog::info("Forwarding DelRequest with key={}", request->key());
    std::shared_ptr<const Shard> shard = shard_discovery_service.get_shard(request->key());
    return shard->Del(request, response);
}