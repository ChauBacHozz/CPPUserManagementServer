cmake_minimum_required(VERSION 3.10)
project(KafkaProjectCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------- Boost -------------------
find_package(Boost REQUIRED COMPONENTS system program_options)

# ------------------- cppkafka -------------------
find_path(CPPKAFKA_INCLUDE_DIR cppkafka/cppkafka.h)
find_library(CPPKAFKA_LIBRARY cppkafka)

# ------------------- librdkafka -------------------
find_path(RDKAFKA_INCLUDE_DIR librdkafka/rdkafka.h)
find_library(RDKAFKA_LIBRARY rdkafka)

# ------------------- OpenSSL -------------------
find_package(OpenSSL REQUIRED)

# ------------------- Apache Arrow -------------------
find_package(Parquet REQUIRED)
find_package(Arrow REQUIRED)

# ------------------- Include directories -------------------
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CPPKAFKA_INCLUDE_DIR}
    ${RDKAFKA_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib
)

# ------------------- Link directories -------------------
link_directories(
    ${CMAKE_SOURCE_DIR}/lib
)

file(GLOB_RECURSE SOURCES "src/*.cpp" "lib/**/*.cpp")

# ------------------- Add executable -------------------
add_executable(main ${SOURCES})


# ------------------- Link libraries -------------------
target_link_libraries(main
    ${Boost_LIBRARIES}
    ${CPPKAFKA_LIBRARY}
    ${RDKAFKA_LIBRARY}
    OpenSSL::SSL
    OpenSSL::Crypto
    Arrow::arrow_shared
    Parquet::parquet_shared
)
