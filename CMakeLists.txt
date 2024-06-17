cmake_minimum_required(VERSION 3.14)

project(MyQtProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Quick Network REQUIRED)

set(SOURCES
    main.cpp
    networkmanager.cpp
    resources.qrc
    qml/main.qml
)

set(HEADERS
    networkmanager.h
)

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
qt5_add_resources(QRC_SOURCES resources.qrc)

add_executable(${PROJECT_NAME}_Executable
    ${SOURCES}
    ${MOC_SOURCES}
    ${QRC_SOURCES}
)

target_link_libraries(${PROJECT_NAME}_Executable Qt5::Core Qt5::Gui Qt5::Quick Qt5::Network)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


add_custom_target(copy_qml_files_${PROJECT_NAME} ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/qml ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qml
)
add_dependencies(${PROJECT_NAME}_Executable copy_qml_files_${PROJECT_NAME})