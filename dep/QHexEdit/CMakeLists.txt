cmake_minimum_required (VERSION 3.13)

project(HexEditQt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

# cmake module part
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# package manager part
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets designer)

# compiler part
set(CMAKE_CXX_STANDARD 17)

add_compile_options(/permissive-)
add_compile_options(/Zc:rvalueCast)
add_compile_options(/Zc:ternary)
add_compile_options(/Zc:referenceBinding)
add_compile_options(/Zc:inline)

add_compile_options(
    /diagnostics:caret
    /W4
    #/WX # for now warnings are ok
    /w14265 # Force enable: 'class': class has virtual functions, but destructor is not virtual
    /w15038 # Force enable: data member 'x' will be initialized after data member 'y'
    #/guard:cf
    #/Z7
    #/d2Zi+
    #/Gm-
    #/Gy
    #/std:c++latest
    #/permissive-
    #/Zc:threadSafeInit-
    #/Zl
)

# project part
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# For now we just make it easy for ourselfs
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
#set(AUTOUIC ON)

set(SOURCES_LIB
    src/chunks.cpp
    include/qhexedit/chunks.h
    src/commands.cpp
    include/qhexedit/commands.h
    src/qhexedit.cpp
    include/qhexedit/qhexedit.h
    src/QHexEditPlugin.cpp
    src/QHexEditPlugin.h
)

source_group(src FILES
    ${SOURCES_LIB}
)

add_library(HexEditQt STATIC
    ${SOURCES_LIB}
)

target_include_directories(HexEditQt
  PUBLIC
    include
  PRIVATE
    src

)

target_compile_definitions(HexEditQt
  PRIVATE
    NOMINMAX
)

target_link_libraries(HexEditQt
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Designer
)

# todo
# restore example
# restore test
