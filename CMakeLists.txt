cmake_minimum_required(VERSION 3.27)
project(positviz)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories("/Users/federico/CLionProjects/cppposit/include")

find_package(Qt5 COMPONENTS
        Core
        Widgets
        REQUIRED)

add_executable(positviz main.cpp
        PositVizWindow.h
        PositVizWindow.cpp)
target_link_libraries(positviz
        Qt5::Core
        Qt5::Widgets
)

