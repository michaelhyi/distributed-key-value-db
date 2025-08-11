#include "dkvdb.h"

#include <spdlog/spdlog.h>

#include "string_util.h"

using dkvdb::DelRequest;
using dkvdb::GetRequest;
using dkvdb::GetResponse;
using dkvdb::SetRequest;
using google::protobuf::Empty;
using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;

Status DkvdbImpl::Get(ServerContext *context, const GetRequest *request, GetResponse *response) {
    if (!request || !context || !response) {
        return Status(StatusCode::INTERNAL, "There was an error processing your request");
    }

    spdlog::info("Processing GetRequest with key={}", request->key());

    if (!StringUtil::valid_string(request->key())) {
        return Status(StatusCode::INVALID_ARGUMENT, "Key must be non-empty");
    }

    std::shared_lock lock(db_mutex);
    auto it = db.find(request->key());
    if (it == db.end()) {
        return Status(StatusCode::NOT_FOUND, "Db item not found");
    }

    response->set_value(it->second);
    return Status::OK;
}

Status DkvdbImpl::Set(ServerContext *context, const SetRequest *request, Empty *response) {
    if (!request || !context || !response) {
        return Status(StatusCode::INTERNAL, "There was an error processing your request");
    }

    spdlog::info("Processing SetRequest with key={}, value={}", request->key(), request->value());

    if (!StringUtil::valid_string(request->key()) || !StringUtil::valid_string(request->value())) {
        return Status(StatusCode::INVALID_ARGUMENT, "Key and value must be non-empty");
    }

    std::unique_lock lock(db_mutex);
    db[request->key()] = request->value();
    return Status::OK;
}

Status DkvdbImpl::Del(ServerContext *context, const DelRequest *request, Empty *response) {
    if (!request || !context || !response) {
        return Status(StatusCode::INTERNAL, "There was an error processing your request");
    }

    spdlog::info("Processing DelRequest with key={}", request->key());

    if (!StringUtil::valid_string(request->key())) {
        return Status(StatusCode::INVALID_ARGUMENT, "Key must be non-empty");
    }

    std::unique_lock lock(db_mutex);
    auto it = db.find(request->key());
    if (it == db.end()) {
        return Status(StatusCode::NOT_FOUND, "Db item not found");
    }

    db.erase(it);
    return Status::OK;
}
