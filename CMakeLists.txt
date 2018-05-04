cmake_minimum_required(VERSION 3.3)

project(csignal)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generating all warnings and errors
if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -pedantic-errors")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

# Print debug info in console
if ( CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_definitions("-DDEBUG")
endif()

# Boost
find_package(Boost 1.40 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# program code
include_directories(include)
file(GLOB SOURCES "src/scanner.cpp"
                , "src/parser.cpp"
                , "src/tables.cpp"
                , "src/listing.cpp"
                , "src/syntaxtree.cpp"
                , "src/main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES})
