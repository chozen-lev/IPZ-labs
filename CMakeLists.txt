cmake_minimum_required(VERSION 3.3)

project(csignal)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lboost_program_options -pedantic-errors")

include_directories(include)

file(GLOB SOURCES
    "src/scanner.cpp",
    "src/parser.cpp",
    "src/tables.cpp",
    "src/listing.cpp",
    "src/syntaxtree.cpp",
    "src/main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
