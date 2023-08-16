cmake_minimum_required(VERSION 3.16)
project(ScreenCapture VERSION 0.1.0 LANGUAGES C CXX)

if (NOT CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED OFF)
    set(CMAKE_C_EXTENSIONS OFF)
endif (NOT CMAKE_C_STANDARD)

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif (NOT CMAKE_CXX_STANDARD)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(blend2d REQUIRED CONFIG REQUIRED)

if (WIN32)
    add_definitions(-D_UNICODE -DUNICODE)
    add_executable(ScreenCapture WIN32 "")
endif (WIN32)

target_sources(ScreenCapture
        PRIVATE
        "ScreenCapture/Font.cpp"
        "ScreenCapture/Font.h"
        "ScreenCapture/Icon.cpp"
        "ScreenCapture/Icon.h"
        "ScreenCapture/main.cpp"
        "ScreenCapture/MainWin.cpp"
        "ScreenCapture/MainWin.h"
        "ScreenCapture/MainWinMask.cpp"
        "ScreenCapture/MainWinMouse.cpp"
        "ScreenCapture/MainWinSystem.cpp"
        "ScreenCapture/MainWinTool.cpp"
        "ScreenCapture/MainWinToolMain.cpp"
        "ScreenCapture/MainWinToolSub.cpp"
        "ScreenCapture/Painter.cpp"
        "ScreenCapture/Painter.h"
        "ScreenCapture/resource.h"
        "ScreenCapture/State.h"
        "ScreenCapture/ToDo.md"
        "ScreenCapture/Util.cpp"
        "ScreenCapture/Util.h"
        "ScreenCapture/Shape/Arrow.cpp"
        "ScreenCapture/Shape/Arrow.h"
        "ScreenCapture/Shape/Box.cpp"
        "ScreenCapture/Shape/Box.h"
        "ScreenCapture/Shape/Ellipse.cpp"
        "ScreenCapture/Shape/Ellipse.h"
        "ScreenCapture/Shape/Eraser.cpp"
        "ScreenCapture/Shape/Eraser.h"
        "ScreenCapture/Shape/History.cpp"
        "ScreenCapture/Shape/History.h"
        "ScreenCapture/Shape/Line.cpp"
        "ScreenCapture/Shape/Line.h"
        "ScreenCapture/Shape/Mosaic.cpp"
        "ScreenCapture/Shape/Mosaic.h"
        "ScreenCapture/Shape/Number.cpp"
        "ScreenCapture/Shape/Number.h"
        "ScreenCapture/Shape/Pen.cpp"
        "ScreenCapture/Shape/Pen.h"
        "ScreenCapture/Shape/Shape.cpp"
        "ScreenCapture/Shape/Shape.h"
        "ScreenCapture/Shape/Text.cpp"
        "ScreenCapture/Shape/Text.h"
)

if (WIN32)
    target_sources(ScreenCapture PRIVATE ${PROJECT_SOURCE_DIR}/ScreenCapture/ScreenCapture.rc "${PROJECT_SOURCE_DIR}/ScreenCapture/dpi.manifest")
    target_link_libraries(${PROJECT_NAME} "DWMAPI.lib" "IMM32.lib")
endif (WIN32)

target_link_libraries(${PROJECT_NAME} blend2d::blend2d)
