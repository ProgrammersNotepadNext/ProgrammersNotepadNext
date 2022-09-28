cmake_minimum_required (VERSION 3.13)

project(ProgrammersNotepad)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

# cmake module part
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# package manager part
#find_package(Qt5 5.14 REQUIRED COMPONENTS Core Gui Widgets designer)

find_package(Qt6 REQUIRED
  COMPONENTS
    Core
    #Gui
    Widgets
    PrintSupport
)

# compiler part
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    /diagnostics:caret
    /W3
    #/WX # for now warnings are ok
    /w14265 # Force enable: 'class': class has virtual functions, but destructor is not virtual
    /w15038 # Force enable: data member 'x' will be initialized after data member 'y'
    #/Z7
    #/d2Zi+
    #/Gm-
    #/Gy
    #/std:c++latest
    /permissive-
    #/Zc:threadSafeInit-
    #/Zl
)

# project part
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(dep)
add_subdirectory(src)
