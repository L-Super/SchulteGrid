cmake_minimum_required(VERSION 3.23)
project(SchulteGrid VERSION 2.2.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Qt/5.15.2/mingw81_64/lib/cmake")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

#注意：这里需要注意编译器路径问题，如果编译器位于D:\Program Files（含有空格），则可能会报路径无法识别错误
#故这里如需版本信息，可使用D:\Qt\Tools\mingw810_64路径下的MinGW
#FAILED: CMakeFiles/SchulteGrid.dir/VersionInfo.rc.obj
#"D:\Program Files\..\CLion\bin\mingw\bin\windres.exe" -O coff ... 'D:\Program' 不是内部或外部命令，也不是可运行的程序或批处理文件。
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "Windows system.So add rc file.Version is ${CMAKE_PROJECT_VERSION}")
    # 设置rc文件生成路径
    set(VERSIONINFO_RC "${CMAKE_BINARY_DIR}/VersionInfo.rc")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/VersionInfo.rc.in" "${VERSIONINFO_RC}")
else()
    message(STATUS "Don't load rc file on other system")
endif()

message(NOTICE "if wrong message is [FAILED: CMakeFiles/SchulteGrid.dir/VersionInfo.rc.obj], please change compiler without space path.")

set(GIT_RESULT "")
find_package(Git QUIET)
#git submodule 初始化、抓取并检出任何嵌套的子模块下载
if(GIT_FOUND)
    message(STATUS "Execute git submodule step")
    execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            OUTPUT_VARIABLE GIT_RESULT
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
else()
    message(WARNING "Git not found")
endif()

if (GIT_RESULT STREQUAL "")
    message(STATUS "Git `submodule update` step is skipped")
else()
    message(STATUS "Git output: ${GIT_RESULT}")
endif()


#add leveldb lib
#添加子目录，并将输出文件存放至${CMAKE_BINARY_DIR}
add_subdirectory(3rdparty/leveldb ${CMAKE_BINARY_DIR}/leveldb)
#include_directories(3rdparty/leveldb/include)

include(FetchContent)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/json
        DOWNLOAD_EXTRACT_TIMESTAMP true
        )
FetchContent_MakeAvailable(json)

FetchContent_Declare(fmt
        URL https://github.com/fmtlib/fmt/archive/refs/tags/9.1.0.tar.gz
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/fmt
        DOWNLOAD_EXTRACT_TIMESTAMP true
        )
FetchContent_MakeAvailable(fmt)

# 如果是Release模式，则去掉终端
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Running ${CMAKE_BUILD_TYPE} mode")
    set(CONSOLE "")
else()
    message(STATUS "Running ${CMAKE_BUILD_TYPE} mode")
    # 去掉终端
    set(CONSOLE WIN32)
endif ()

add_executable(SchulteGrid ${CONSOLE} main.cpp
        MenuWidget.cpp MenuWidget.h MenuWidget.ui
        WhichModeWidget.cpp WhichModeWidget.h WhichModeWidget.ui
        GameWidget.cpp GameWidget.h GameWidget.ui
        Common.h
        RandomShuffle.h
        resources.qrc
        ${VERSIONINFO_RC}
        LeveldbPimpl.cpp LeveldbPimpl.h
        RecordWidget.cpp RecordWidget.h RecordWidget.ui)

target_link_libraries(SchulteGrid
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        leveldb
        nlohmann_json::nlohmann_json
        fmt::fmt-header-only
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
    # 复制其他库文件到可执行文件所在的目录
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/bin/libgcc_s_seh-1.dll"
            "${QT_INSTALL_PATH}/bin/libstdc++-6.dll"
            "${QT_INSTALL_PATH}/bin/libwinpthread-1.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            )
endif ()
