#pragma once

#include <grpcpp/impl/service_type.h>

void RunServer(grpc::Service* service, int port = 50051);
