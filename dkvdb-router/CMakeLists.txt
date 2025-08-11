cmake_minimum_required(VERSION 3.19)
project(dkvdb-router)

include(../common.cmake)

get_filename_component(dkvdb_router_proto "../dkvdb-protos/dkvdb_router.proto" ABSOLUTE)
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

add_library(
    dkvdb_router_grpc_proto
    ${dkvdb_router_proto_srcs}
    ${dkvdb_router_proto_hdrs}
    ${dkvdb_router_grpc_srcs}
    ${dkvdb_router_grpc_hdrs}
)
target_link_libraries(
    dkvdb_router_grpc_proto
    ${_GRPC_GRPCPP}
    ${_REFLECTION}
    ${_PROTOBUF_LIBPROTOBUF}
)

add_executable(
    dkvdb_router
    dkvdb_router.cc
    dkvdb_router.h
    main.cc
)
target_link_libraries(
    dkvdb_router
    dkvdb_router_grpc_proto
    dkvdb_server
    dkvdb_util
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)
