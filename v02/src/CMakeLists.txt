cmake_minimum_required(VERSION 3.16.0)
project(readyspice)

set(VERSION 0.1.0)
set(KF5_MIN_VERSION 5.14.0)

find_package(ECM ${KF5_MIN_VERSION} CONFIG REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_GENERATOR "Unix Makefiles")

set(CMAKE_CXX_FLAGS
${CMAKE_CXX_FLAGS} -Wall
)

set(CMAKE_PREFIX_PATH
/home/admins/Qt5.14.2/5.14.2/gcc_64/lib/cmake
)

set(CMAKE_MODULE_PATH
${ECM_MODULE_PATH}
${ECM_KDE_MODULE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

find_package(KF5 REQUIRED COMPONENTS
CoreAddons
I18n
WidgetsAddons
Parts
)

find_package(Qt5 REQUIRED COMPONENTS
Core
Gui
Widgets
)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEClangFormat OPTIONAL RESULT_VARIABLE KDEClangFormat_FOUND)
include(ECMSetupVersion)
include(ECMQtDeclareLoggingCategory)
include(ECMInstallIcons)
include(FeatureSummary)

ecm_setup_version(${VERSION}
    VARIABLE_PREFIX READYSPICE
    VERSION_HEADER rdv_app_version.h
)

ecm_qt_declare_logging_category(readyspice_SRCS
    HEADER rdv_app_debug.h
    IDENTIFIER RDV_LOG
    CATEGORY_NAME org.kde.ready.spice
    DEFAULT_SEVERITY Warning
)

set(gui_UI
rdv_app_context_help_widget.ui
)

ki18n_wrap_ui(gui_STAT_SRCS
${gui_UI}
)

SET(readyspice_SRCS
${gui_STAT_SRCS}
rdv_app_debug.cpp
rdv_app_circuit_document.cpp
rdv_app_circuit_icn_document.cpp
rdv_app_doc_manager.cpp
rdv_app_document.cpp
rdv_app_flow_code_document.cpp
rdv_app_flow_icn_document.cpp
rdv_app_icn_document.cpp
rdv_app_item_document.cpp
rdv_app_item_selector.cpp
rdv_app_main_window.cpp
rdv_app_mechanics_document.cpp
rdv_app_project_manager.cpp
rdv_app_readyspice.cpp
rdv_app_text_document.cpp
rdv_app_tool_view.cpp
rdv_app_variant.cpp
rdv_app_view_area.cpp
rdv_app_view_container.cpp
rdv_app_view.cpp
rdv_app_side_bar.cpp
rdv_app_splitter.cpp
rdv_app_gui_client.cpp
rdv_app_ilv_item.cpp
rdv_app_component_selector.cpp
rdv_app_sub_circuit.cpp
rdv_app_item_editor.cpp
rdv_app_context_help.cpp
rdv_app_language_manager.cpp
rdv_app_oscilloscope.cpp
rdv_app_flow_part_selector.cpp
rdv_app_symbol_viewer.cpp
rdv_app_item_library.cpp
rdv_app_scope_screen.cpp
rdv_app_property_editor.cpp
rdv_app_component_model_widget.cpp
rdv_app_orientation_widget.cpp
)

add_definitions(-fPIC)

add_executable(readyspice
main.cpp
${readyspice_SRCS}
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ../bin
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
Qt5::Core
Qt5::Gui
Qt5::Widgets
KF5::CoreAddons
KF5::I18n
KF5::WidgetsAddons
KF5::Parts
)
