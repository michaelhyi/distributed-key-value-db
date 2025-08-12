cmake_minimum_required(VERSION 3.19)
project(db-router)

include(../common.cmake)

add_executable(
    router
    main.cc
    router.cc
    router.h
)
target_link_libraries(
    router
    db_grpc_proto
    router_grpc_proto
    common
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)
