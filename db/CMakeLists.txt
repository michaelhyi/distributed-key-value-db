cmake_minimum_required(VERSION 3.19)
project(db)

include(../common.cmake)

find_path(ZOOKEEPER_INCLUDE_DIR zookeeper/zookeeper.h)
find_library(ZOOKEEPER_LIBRARY zookeeper_mt)

if (NOT ZOOKEEPER_INCLUDE_DIR OR NOT ZOOKEEPER_LIBRARY)
    message(FATAL_ERROR "Could not find ZooKeeper")
endif()

add_executable(
    db
    src/db_util.cc
    src/db_util.h
    src/db.cc
    src/db.h
    src/main.cc
    src/router_client.cc
    src/router_client.h
    src/zookeeper_service.cc
    src/zookeeper_service.h
)
target_include_directories(
    db
    PRIVATE ${ZOOKEEPER_INCLUDE_DIR}
)
target_link_libraries(
    db
    common
    db_grpc_proto
    router_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    ${ZOOKEEPER_LIBRARY}
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)
