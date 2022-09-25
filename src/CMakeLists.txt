cmake_minimum_required (VERSION 3.13)

project(Hexactly)

# project part
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# For now we just make it easy for ourselfs
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)

set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    optionsdialog.cpp
    optionsdialog.h
    searchdialog.cpp
    searchdialog.h
)

source_group(src FILES
    ${SOURCES}
)

set(SOURCES_GUI
    gui/editortab.cpp
    gui/editortab.h
    gui/tab.cpp
    gui/tab.h
    gui/tabbar.cpp
    gui/tabbar.h
    gui/tabwidget.cpp
    gui/tabwidget.h
    gui/hexeditor.cpp
    gui/hexeditor.h
    gui/glyph_button.cpp
    gui/glyph_button.h
)

source_group(src\\gui FILES
    ${SOURCES_GUI}
)

qt5_wrap_ui(QT_SOURCES_UI
    optionsdialog.ui
    searchdialog.ui
)

source_group(src\\gui\\generated FILES
    ${QT_SOURCES_UI}
)

set(RESOURCES
    hexactly.qrc
)

qt5_add_resources(QT_RESOURCES
    ${RESOURCES}
)

add_executable(Hexactly
    ${SOURCES}
    ${SOURCES_GUI}
    ${QT_RESOURCES}
    ${QT_SOURCES_UI}
)

target_include_directories(Hexactly
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Hexactly
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    HexEditQt
)

target_compile_definitions(Hexactly
  PRIVATE
    NOMINMAX
)

set_target_properties(Hexactly PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$(Configuration)
)
