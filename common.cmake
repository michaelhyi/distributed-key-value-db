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

find_package(spdlog REQUIRED)

add_library(
    common 
    "${CMAKE_CURRENT_LIST_DIR}/common/network_util.cc"
    "${CMAKE_CURRENT_LIST_DIR}/common/network_util.h"
    "${CMAKE_CURRENT_LIST_DIR}/common/server.cc"
    "${CMAKE_CURRENT_LIST_DIR}/common/server.h"
    "${CMAKE_CURRENT_LIST_DIR}/common/string_util.cc"
    "${CMAKE_CURRENT_LIST_DIR}/common/string_util.h"
)
target_include_directories(
    common
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/common"
)
target_link_libraries(
    common
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)
