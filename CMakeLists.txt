cmake_minimum_required(VERSION 3.3)

project(csignal)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_program_options")

include_directories(include)

file(GLOB SOURCES
    "src/scanner.cpp",
    "src/parser.cpp",
    "src/listing.cpp",
    "src/syntaxtree.cpp",
    "src/main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
