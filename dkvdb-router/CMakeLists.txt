cmake_minimum_required(VERSION 3.19)
project(dkvdb-router)

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

get_filename_component(dkvdb_router_proto "dkvdb_router.proto" ABSOLUTE)
get_filename_component(dkvdb_router_proto_path "${dkvdb_router_proto}" PATH)

set(dkvdb_router_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/dkvdb_router.pb.cc")
set(dkvdb_router_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/dkvdb_router.pb.h")
set(dkvdb_router_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/dkvdb_router.grpc.pb.cc")
set(dkvdb_router_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/dkvdb_router.grpc.pb.h")
add_custom_command(
    OUTPUT "${dkvdb_router_proto_srcs}" "${dkvdb_router_proto_hdrs}" "${dkvdb_router_grpc_srcs}" "${dkvdb_router_grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${dkvdb_router_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${dkvdb_router_proto}"
    DEPENDS "${dkvdb_router_proto}"
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(dkvdb_router_grpc_proto
    ${dkvdb_router_proto_srcs}
    ${dkvdb_router_proto_hdrs}
    ${dkvdb_router_grpc_srcs}
    ${dkvdb_router_grpc_hdrs}
)
target_link_libraries(dkvdb_router_grpc_proto
    ${_GRPC_GRPCPP}
    ${_REFLECTION}
    ${_PROTOBUF_LIBPROTOBUF}
)

add_executable(
    dkvdb_router
    dkvdb_router.cc
    dkvdb_router.h
    main.cc
    server.cc
    server.h
    util.cc
    util.h
)
target_link_libraries(
    dkvdb_router
    dkvdb_router_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)
