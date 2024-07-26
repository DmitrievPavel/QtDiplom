cmake_minimum_required(VERSION 3.5)

project(airport VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent PrintSupport Sql)


set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    graphic.cpp
    graphic.h
    dialog.h
    dialog.cpp
    dialog.ui
    database.h
    database.cpp

)


add_executable(airport
    ${PROJECT_SOURCES}
)
add_compile_definitions(QCUSTOMPLOT_USE_LIBRARY)
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(airport Qt6::Widgets
                                      Qt6::Concurrent
                                      Qt6::PrintSupport
                                      Qt6::Sql
                                      qcustomplot2.dll
                                      libcrypto-3-x64
                                      libiconv-2
                                      libintl-9
                                      libpq
                                      libssl-3-x64)
