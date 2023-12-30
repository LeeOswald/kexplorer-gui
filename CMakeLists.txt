cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(KX_CXX_FEATURES cxx_std_20)

function(get_version_from_file VER_FILE_NAME)
    file(READ ${VER_FILE_NAME} KX_VERSION_RAW)
    # Remove trailing whitespaces and/or newline
    string(STRIP ${KX_VERSION_RAW} KX_VERSION_)
    set(KX_VERSION ${KX_VERSION_} CACHE STRING
        "Project version determined from version.txt" FORCE
    )
    message(STATUS "Determined project version ${KX_VERSION}")
endfunction()


get_version_from_file("version.txt")

project(kexplorer-client VERSION ${KX_VERSION})

if(NOT CMAKE_BUILD_TYPE)
    message(WARNING "CMAKE_BUILD_TYPE isn't defined. Debug value will be used by default.")
    set(CMAKE_BUILD_TYPE Debug)
else()
    if(${CMAKE_BUILD_TYPE} MATCHES "^[Rr][Ee][Ll][Ee][Aa][Ss][Ee]$")
        set(CMAKE_BUILD_TYPE Release)
    elseif(${CMAKE_BUILD_TYPE} MATCHES "^[Dd][Ee][Bb][Uu][Gg]$")
        set(CMAKE_BUILD_TYPE Debug)
    else()
        message(WARNING "CMAKE_BUILD_TYPE isn't Release or Debug. Debug value will be used by default.")
        set(CMAKE_BUILD_TYPE Debug)
    endif()
endif()

set(KX_LINUX 0)
set(KX_WINDOWS 0)

if(WIN32)
    set(KX_WINDOWS 1)
elseif(UNIX AND NOT APPLE)
    set(KX_LINUX 1)
else()
    message(FATAL_ERROR "Unsupported OS")
endif()


if(MSVC)
else()
    add_link_options(-rdynamic) # enable stack capture
endif()

# require Qt6
find_package(Qt6Core REQUIRED)
find_package(Qt6Gui REQUIRED)
find_package(Qt6Widgets REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Qt6Widgets_INCLUDES also includes the include directories for QtCore and QtGui
include_directories(${Qt6Widgets_INCLUDES})
# We need to add -DQT_WIDGETS_LIB when using QtWidgets in Qt 6
add_definitions(${Qt6Widgets_DEFINITIONS})

if(KX_LINUX)
    # require pthreads
    find_package(Threads REQUIRED)
    set(PLATFORM_LIBRARIES Threads::Threads)
endif()

# require Boost
find_package(Boost REQUIRED COMPONENTS system program_options)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

if(WIN32)
    # disable autolinking in boost
    add_definitions(-DBOOST_ALL_NO_LIB)
    # force all boost libraries to dynamic link
    add_definitions(-DBOOST_ALL_DYN_LINK)
endif()

# force shared CRT
if(MSVC)
    cmake_policy(SET CMP0091 NEW)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

# Windows-specific settings
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/kexplorer-version.h.in kexplorer-version.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${PROJECT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/submodules/kexporer-server/include ${CMAKE_CURRENT_SOURCE_DIR}/include)



set(KX_CLIENTLIB kxclient)
set(KX_APP kexplorer)

add_subdirectory(submodules/kexplorer-server)
#add_subdirectory(src/kxclient)
add_subdirectory(src/kexplorer)
