cmake_minimum_required(VERSION 3.0)
project(readyspice LANGUAGES CXX)
set(VERSION 0.1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
)

add_executable(readyspice
    main.cpp
    rdv_app_main_window.cpp
)

target_link_libraries(readyspice PRIVATE
    Qt6::Widgets
)
