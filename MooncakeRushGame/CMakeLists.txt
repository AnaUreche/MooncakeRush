#-------------------------------------------------------------------------------------------
# Cmake configuration based on
# Jon Macey from different sources like coursework and demos
# [Accessed 2021]
#-------------------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.5)
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

project(MooncakeRushGUIBUILD LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(NGL CONFIG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)



find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
)


    add_executable(MooncakeRushGUI)

    target_sources(MooncakeRushGUI PRIVATE
            src/main.cpp
            src/MainWindow.cpp
            src/NGLScene.cpp
            src/Player.cpp
            src/Obstacle.cpp
            src/Map.cpp
            include/NGLScene.h
            include/Player.h
            include/Obstacle.h
            include/Map.h
            include/MainWindow.h
            ui/MainWindow.ui
        )

target_link_libraries(MooncakeRushGUI PRIVATE NGL Qt${QT_VERSION_MAJOR}::Widgets)


add_custom_target(CopyResources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:MooncakeRushGUI>/shaders

    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/textures
    $<TARGET_FILE_DIR:MooncakeRushGUI>/textures

    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/models
    $<TARGET_FILE_DIR:MooncakeRushGUI>/models
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/fonts
    $<TARGET_FILE_DIR:MooncakeRushGUI>/fonts)
