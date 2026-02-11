cmake_minimum_required(VERSION 3.24)
project(PocketBank LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable sanitizers for debug (disabled on Alpine/musl - causes incompatibilities)
# if(CMAKE_BUILD_TYPE MATCHES "Debug")
#   add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
#   add_link_options(-fsanitize=address,undefined)
# endif()

# vcpkg integration expected via devcontainer settings
find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
# find_package(httplib CONFIG REQUIRED)  # Not in Alpine repos
find_package(SQLite3 REQUIRED)
find_package(GTest CONFIG REQUIRED)
# find_package(benchmark CONFIG REQUIRED)  # Not in Alpine repos

# Library
file(GLOB POCKETBANK_SOURCES CONFIGURE_DEPENDS
     "src/*.cpp")
add_library(pocketbank_lib ${POCKETBANK_SOURCES})
target_include_directories(pocketbank_lib PUBLIC include)
target_link_libraries(pocketbank_lib
  PUBLIC
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    SQLite::SQLite3
)

# Executable
add_executable(pocketbank src/main.cpp)
# target_link_libraries(pocketbank PRIVATE pocketbank_lib httplib::httplib)
target_link_libraries(pocketbank PRIVATE pocketbank_lib)

# Tests
enable_testing()
add_executable(pocketbank_tests tests/test_basic.cpp tests/test_ledger.cpp)
target_link_libraries(pocketbank_tests PRIVATE pocketbank_lib GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(pocketbank_tests)

# Benchmarks (disabled - benchmark library not available in Alpine)
# add_executable(pocketbank_bench benchmarks/bench_ledger.cpp)
# target_link_libraries(pocketbank_bench PRIVATE pocketbank_lib benchmark::benchmark)

# Install (later for packaging)
install(TARGETS pocketbank pocketbank_lib)