cmake_minimum_required(VERSION 3.19)
project(db)

include(../common.cmake)

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

add_executable(
    db
    db.cc
    db.h
    main.cc
    router_client.cc
    router_client.h
    router_util.cc
    router_util.h
)
target_link_libraries(
    db
    db_grpc_proto
    router_grpc_proto
    common
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)
