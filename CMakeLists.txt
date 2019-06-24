cmake_minimum_required(VERSION 3.13)

project(QtExamples
    VERSION 0.0.1
    DESCRIPTION "Examples and concepts I had to use at some point with Qt"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Network)

add_subdirectory(tcp)
