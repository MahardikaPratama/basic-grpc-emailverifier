cmake_minimum_required(VERSION 3.15)
project(BasicGrpcEmailVerifier)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

set(PROTO_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/proto/emailverifier.proto
)

set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTO_SRC})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTO_SRC})

add_executable(client src/client.cpp ${PROTO_SRCS} ${GRPC_SRCS})
target_include_directories(client PRIVATE ${PROTO_SRC_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(client gRPC::grpc++ protobuf::libprotobuf gpr absl_synchronization)

add_executable(server src/server.cpp ${PROTO_SRCS} ${GRPC_SRCS})
target_include_directories(server PRIVATE ${PROTO_SRC_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(server gRPC::grpc++ protobuf::libprotobuf gpr absl_synchronization)