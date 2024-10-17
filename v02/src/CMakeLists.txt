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

add_definitions(-fPIC)

add_executable(readyspice
main.cpp
rdv_app_readyspice.cpp
rdv_app_view_area.cpp
rdv_app_project_manager.cpp
rdv_app_item_selector.cpp
rdv_app_tool_view.cpp
rdv_app_variant.cpp
rdv_app_main_window.cpp
rdv_app_doc_manager.cpp
rdv_app_document.cpp
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ../bin
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
Qt5::Widgets
KF5::CoreAddons
KF5::I18n
KF5::WidgetsAddons
KF5::Parts
)
