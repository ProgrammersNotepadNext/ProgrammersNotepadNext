set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)

set(SOURCES
    application.cpp
    application.h
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
)

source_group(src\\gui FILES
    ${SOURCES_GUI}
)

qt_wrap_ui(QT_SOURCES_UI
    optionsdialog.ui
    searchdialog.ui
)

source_group(src\\gui\\generated FILES
    ${QT_SOURCES_UI}
)

set(RESOURCES
    programmersnotepadnext.qrc
)

qt_add_resources(QT_RESOURCES
    ${RESOURCES}
)

add_executable(ProgrammersNotepadNext
    ${SOURCES}
    ${SOURCES_GUI}
    ${QT_RESOURCES}
    ${QT_SOURCES_UI}
)

target_include_directories(ProgrammersNotepadNext
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ProgrammersNotepadNext
    Qt::Core
    Qt::Gui
    Qt::Widgets
    HexEditQt
)

target_compile_definitions(ProgrammersNotepadNext
  PRIVATE
    NOMINMAX
    # for now we must define this because qt6 isn't c++23 compliant.
    _SILENCE_ALL_CXX23_DEPRECATION_WARNINGS
)

set_target_properties(ProgrammersNotepadNext PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$(Configuration)
)
