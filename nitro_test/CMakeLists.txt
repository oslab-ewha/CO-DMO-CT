cmake_minimum_required(VERSION 2.8)
project(IoT_TEE)

list(APPEND CMAKE_MODULE_PATH "/${CMAKE_INSTALL_LIBDIR}/cmake")

#if (DEFINED CMAKE_PREFIX_PATH)
#    file(TO_CMAKE_PATH "${CMAKE_PREFIX_PATH}" CMAKE_PREFIX_PATH)
#endif()

#if (DEFINED CMAKE_INSTALL_PREFIX)
#    file(TO_CMAKE_PATH "${CMAKE_INSTALL_PREFIX}" CMAKE_INSTALL_PREFIX)
#endif()

# This is required in order to append /lib/cmake to each element in CMAKE_PREFIX_PATH
#set(AWS_MODULE_DIR "/${CMAKE_INSTALL_LIBDIR}/cmake")
#string(REPLACE ";" "${AWS_MODULE_DIR};" AWS_MODULE_PATH "${CMAKE_PREFIX_PATH}${AWS_MODULE_DIR}")
# Append that generated list to the module search path
#list(APPEND CMAKE_MODULE_PATH ${AWS_MODULE_PATH})

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

#add_executable(iot_device iot_device.c)
#target_link_libraries(iot_device paho-mqtt3cs)

#add_executable(edge_gateway edge_gateway.c)
#target_link_libraries(edge_gateway paho-mqtt3cs)

add_executable(enclave enclave.c)
target_link_libraries(enclave aws-nitro-enclaves-sdk-c aws-c-auth aws-c-http aws-c-compression aws-c-io aws-c-sdkutils aws-c-cal aws-c-common json-c s2n m nsm crypto pthread dl)

install(TARGETS enclave DESTINATION bin)

