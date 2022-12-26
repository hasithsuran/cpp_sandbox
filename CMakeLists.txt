cmake_minimum_required(VERSION 3.5)

set(PROGRAM "CppDemo")
set(SOURCE_DIR "src")

project(${PROGRAM}
        VERSION 0.0.1
        DESCRIPTION "C++ demonstration app"
        LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "-Wall")

option(BUILD_BITWISE_DEMO "Enter building bitwise demonstration" OFF)
option(DBUILD_VECTOR_DEMO "Enter building STL vector demonstration" OFF)



add_executable(${PROGRAM} ${SOURCE_DIR}/main.cpp)
target_compile_features(${PROGRAM} PRIVATE cxx_std_20)

if(${BUILD_BITWISE_DEMO})
    message(STATUS "Preparting to build bitwise demo...")
    target_compile_definitions(${PROGRAM} PRIVATE USE_BITWISE_DEMO)
endif()

if(${BUILD_VECTOR_DEMO})
    message(STATUS "Preparting to build vector demo...")
    target_compile_definitions(${PROGRAM} PRIVATE USE_VECTOR_DEMO)
endif()

#fetch submodules

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update started...")
        message(STATUS "Hint: can remove --remote option to stick with last added commit of submodule")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --remote
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#use git submodule status to check all submodule status
#use git rm --cached path_to_submodule to remove cachd submodule

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/STL/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(external/STL)
add_subdirectory(external/core)
list(APPEND INCLUDE_DIRS "include" "external/STL/include" "external/core/include")

target_include_directories(${PROGRAM} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROGRAM} PRIVATE STL_Lib PRIVATE core_lib)

