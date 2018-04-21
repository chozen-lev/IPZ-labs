cmake_minimum_required(VERSION 3.3)

project(Translator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

file(GLOB SOURCES
    "src/scanner.cpp",
    "src/parser.cpp",
    "src/listing.cpp",
    "src/main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
