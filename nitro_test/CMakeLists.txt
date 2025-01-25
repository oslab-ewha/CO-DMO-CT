cmake_minimum_required(VERSION 2.8)
project(IoT_TEE)

list(APPEND CMAKE_MODULE_PATH "/${CMAKE_INSTALL_LIBDIR}/cmake")

#include(AwsCFlags)
#include(AwsCheckHeaders)
#include(AwsSharedLibSetup)
#include(AwsSanitizers)
#include(AwsFindPackage)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/lib/cmake")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "/usr")

#aws_set_common_properties(enclave)

#include_directories(${PahoMqttC_INCLUDE_DIRS})
#link_directories(${PahoMqttC_LIBRARY_DIRS})

#find_package(gRPC REQUIRED)
#find_package(Protobuf REQUIRED)

include_directories(${gRPC_INCLUDE_DIRS} ${Protobuf_INCLUDE_DIRS})
link_directories(${gRPC_LIBRARY_DIRS} ${Protobuf_LIBRARY_DIRS})

add_executable(iot_device iot_device.c)
target_link_libraries(iot_device paho-mqtt3cs)

add_executable(enclave_server enclave_server.c)
target_link_libraries(edge_gateway paho-mqtt3cs)

add_executable(iiot_emulator iiot_emulator.c)
target_link_libraries(enclave aws-nitro-enclaves-sdk-c aws-c-auth aws-c-http aws-c-compression aws-c-io aws-c-sdkutils aws-c-cal aws-c-common json-c s2n m nsm crypto pthread dl)

install(TARGETS enclave DESTINATION bin)

