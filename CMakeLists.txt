# Minimum CMake required
cmake_minimum_required(VERSION 3.15)

#C++ standard
set(CMAKE_CXX_STANDARD 17)

# Project
project(flowclient)

# Protobuf
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

# Protobuf-compiler
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

# gRPC
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")
set(_GRPC_GRPCPP gRPC::grpc++)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

# Proto file
get_filename_component(proto "proto/flowprotobuf.proto" ABSOLUTE)
get_filename_component(proto_path "${proto}" PATH)

# Generated sources
set(proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/flowprotobuf.pb.cc")
set(proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/flowprotobuf.pb.h")
set(grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/flowprotobuf.grpc.pb.cc")
set(grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/flowprotobuf.grpc.pb.h")

add_custom_command(
      OUTPUT "${proto_srcs}" "${proto_hdrs}" "${grpc_srcs}" "${grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS 	--grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        	--cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        	-I "${proto_path}"
        	--plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        	"${proto}"
      		DEPENDS "${proto}"
      )

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Crypto compiler flags

# Targets (client)
foreach(_target Samples)
  add_executable(${_target} "src/${_target}.cc" ${proto_srcs} ${grpc_srcs})
  target_link_libraries(${_target} ${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})
endforeach()

# Unit Test
#enable_testing()
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
link_directories(${Boost_LIBRARY_DIRS})
set(test test)
foreach(test test)
  add_executable(${test} "tests/${test}.cc"
    ${proto_srcs}
    ${grpc_srcs})
  target_link_libraries(${test}
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    ${Boost_LIBRARIES}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
endforeach()
add_test(client_test ${test})





