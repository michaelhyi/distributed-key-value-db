cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
    find_program(_PROTOBUF_PROTOC protoc)
else()
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

find_package(gRPC CONFIG REQUIRED)
set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

find_path(ZOOKEEPER_INCLUDE_DIR zookeeper/zookeeper.h)
find_library(ZOOKEEPER_LIBRARY zookeeper_mt)

if (NOT ZOOKEEPER_INCLUDE_DIR OR NOT ZOOKEEPER_LIBRARY)
    message(FATAL_ERROR "Could not find ZooKeeper")
endif()

find_package(spdlog REQUIRED)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_library(
    common 
    "${CMAKE_CURRENT_LIST_DIR}/common/src/zookeeper/zookeeper_service.cc"
    "${CMAKE_CURRENT_LIST_DIR}/common/src/zookeeper/zookeeper_service.h"
    "${CMAKE_CURRENT_LIST_DIR}/common/src/network_util.cc"
    "${CMAKE_CURRENT_LIST_DIR}/common/src/network_util.h"
    "${CMAKE_CURRENT_LIST_DIR}/common/src/server.h"
    "${CMAKE_CURRENT_LIST_DIR}/common/src/server.tpp"
    "${CMAKE_CURRENT_LIST_DIR}/common/src/string_util.cc"
    "${CMAKE_CURRENT_LIST_DIR}/common/src/string_util.h"
)
target_include_directories(
    common
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/common/src"
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/common/src/zookeeper"
    PRIVATE ${ZOOKEEPER_INCLUDE_DIR}
)
target_link_libraries(
    common
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    ${ZOOKEEPER_LIBRARY}
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)

get_filename_component(db_proto "../protobufs/db.proto" ABSOLUTE)
get_filename_component(router_proto "../protobufs/router.proto" ABSOLUTE)
get_filename_component(proto_path "${db_proto}" PATH)

set(db_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/db.pb.cc")
set(db_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/db.pb.h")
set(db_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/db.grpc.pb.cc")
set(db_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/db.grpc.pb.h")
set(router_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/router.pb.cc")
set(router_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/router.pb.h")
set(router_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/router.grpc.pb.cc")
set(router_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/router.grpc.pb.h")
add_custom_command(
    OUTPUT "${db_proto_srcs}" "${db_proto_hdrs}" "${db_grpc_srcs}" "${db_grpc_hdrs}" "${router_proto_srcs}" "${router_proto_hdrs}" "${router_grpc_srcs}" "${router_grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${db_proto}" "${router_proto}"
    DEPENDS "${db_proto}" "${router_proto}"
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(
    db_grpc_proto
    ${db_proto_srcs}
    ${db_proto_hdrs}
    ${db_grpc_srcs}
    ${db_grpc_hdrs}
)
target_link_libraries(
    db_grpc_proto
    ${_GRPC_GRPCPP}
    ${_REFLECTION}
    ${_PROTOBUF_LIBPROTOBUF}
)

add_library(
    router_grpc_proto
    ${router_proto_srcs}
    ${router_proto_hdrs}
    ${router_grpc_srcs}
    ${router_grpc_hdrs}
)
target_link_libraries(
    router_grpc_proto
    ${_GRPC_GRPCPP}
    ${_REFLECTION}
    ${_PROTOBUF_LIBPROTOBUF}
)

enable_testing()

add_executable(
    common_test
    "${CMAKE_CURRENT_LIST_DIR}/common/test/string_util_test.cc"
)
target_link_libraries(
    common_test
    common
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(common_test)
