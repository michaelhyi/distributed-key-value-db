cmake_minimum_required(VERSION 3.19)
project(db-router)

include(../common.cmake)

add_executable(
    router
    src/db_forward.cc
    src/db_forward.h
    src/main.cc
    src/shard_discovery.cc
    src/shard_discovery.h
    src/shard.cc
    src/shard.h
)
target_link_libraries(
    router
    common
    db_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)
