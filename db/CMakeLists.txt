cmake_minimum_required(VERSION 3.19)
project(db)

include(../common.cmake)

add_executable(
    db
    src/db_util.cc
    src/db_util.h
    src/db.cc
    src/db.h
    src/main.cc
    src/router_client.cc
    src/router_client.h
)
target_link_libraries(
    db
    common
    db_grpc_proto
    router_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)
