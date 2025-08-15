cmake_minimum_required(VERSION 3.19)
project(db-router)

include(../common.cmake)

add_executable(
    router
    src/db_forward.cc
    src/db_forward.h
    src/indexed_set.h
    src/indexed_set.tpp
    src/main.cc
    src/router.cc
    src/router.h
    src/shard_discovery.cc
    src/shard_discovery.h
    src/shard.cc
    src/shard.h
)
target_link_libraries(
    router
    common
    db_grpc_proto
    router_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)

add_executable(
    router_test
    test/indexed_set_test.cc
)
target_include_directories(
    router_test
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(
    router_test
    GTest::gtest_main
)
gtest_discover_tests(router_test)
