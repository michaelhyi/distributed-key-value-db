cmake_minimum_required(VERSION 3.19)
project(db)

include(../common.cmake)

add_executable(
    db
    db_util.cc
    db_util.h
    db.cc
    db.h
    main.cc
    router_client.cc
    router_client.h
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
