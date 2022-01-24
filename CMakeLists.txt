cmake_minimum_required(VERSION 3.10.0)

project(vision_app)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Widgets)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(vision_app
   mainwindow.ui
   mainwindow.cpp
   videoCapture.cpp
   main.cpp
   resources.qrc)

target_link_libraries(vision_app
   Qt5::Widgets
   ${OpenCV_LIBS}
   )