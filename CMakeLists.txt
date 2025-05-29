cmake_minimum_required(VERSION 3.10)
project(KafkaProjectCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost with both system and program_options components
find_package(Boost REQUIRED COMPONENTS system program_options)

# Find cppkafka
find_path(CPPKAFKA_INCLUDE_DIR cppkafka/cppkafka.h)
find_library(CPPKAFKA_LIBRARY cppkafka)

# Find librdkafka
find_path(RDKAFKA_INCLUDE_DIR librdkafka/rdkafka.h)
find_library(RDKAFKA_LIBRARY rdkafka)

# OpenSSL
find_package(OpenSSL REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CPPKAFKA_INCLUDE_DIR}
    ${RDKAFKA_INCLUDE_DIR}
    src
)

# Add producer executable
add_executable(producer src/producer.cpp)

# Add consumer executable
add_executable(consumer src/consumer.cpp)

# Link libraries for producer
target_link_libraries(producer
    ${CPPKAFKA_LIBRARY}
    ${RDKAFKA_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}  # Add this
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Link libraries for consumer
target_link_libraries(consumer
    ${CPPKAFKA_LIBRARY}
    ${RDKAFKA_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}  # Add this
    OpenSSL::SSL
    OpenSSL::Crypto
)