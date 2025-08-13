#include "shard.h"

using db::GetRequest;
using db::GetResponse;
using db::SetRequest;
using db::DelRequest;

using grpc::Status;
using grpc::ClientContext;
using google::protobuf::Empty;

Status Shard::Get(const GetRequest *request, GetResponse *response) const {
    ClientContext context;
    return _stub->Get(&context, *request, response);
}

Status Shard::Set(const SetRequest *request, Empty *response) const {
    ClientContext context;
    return _stub->Set(&context, *request, response);
}

Status Shard::Del(const DelRequest *request, Empty *response) const {
    ClientContext context;
    return _stub->Del(&context, *request, response);
}
