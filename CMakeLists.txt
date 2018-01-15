cmake_minimum_required(VERSION 3.7)
project(avltree)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(avltree)

set(SOURCE_FILES main.cpp)
add_executable(Main ${SOURCE_FILES})

target_link_libraries(Main LINK_PUBLIC avltree)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN Doxyfile.in)
    set(DOXYGEN_OUT doc)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile.in
            WORKING_DIRECTORY avltree
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

# GoogleTest

# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

add_subdirectory(test)

enable_testing()

add_test(testAvlTree test/testAvlTree --gtest_output=xml:report.xml)
