cmake_minimum_required(VERSION 3.19)
project(db-router)

include(../common.cmake)

get_filename_component(router_proto "../protobufs/router.proto" ABSOLUTE)
get_filename_component(router_proto_path "${router_proto}" PATH)

set(router_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/router.pb.cc")
set(router_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/router.pb.h")
set(router_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/router.grpc.pb.cc")
set(router_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/router.grpc.pb.h")
add_custom_command(
    OUTPUT "${router_proto_srcs}" "${router_proto_hdrs}" "${router_grpc_srcs}" "${router_grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${router_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${router_proto}"
    DEPENDS "${router_proto}"
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

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

add_executable(
    router
    router.cc
    router.h
    main.cc
)
target_link_libraries(
    router
    router_grpc_proto
    common
    common
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)
