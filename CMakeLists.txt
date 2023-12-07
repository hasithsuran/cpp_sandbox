cmake_minimum_required(VERSION 3.5)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR “In-source build detected!”)
endif()

set(PROGRAM "CppDemo")
set(SOURCE_DIR "src")

project(${PROGRAM}
        VERSION 0.0.1
        DESCRIPTION "C++ demonstration app"
        LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "-Wall")

option(BUILD_BITWISE_DEMO "Build bitwise demonstration" OFF)
option(BUILD_VECTOR_DEMO "Build STL vector demonstration" OFF)
option(BUILD_LAMBDA_DEMO "Build lambda demonstration" OFF)
option(BUILD_MAP_DEMO "Build STL map demonstration" OFF)
option(BUILD_BASIC_MEMORY_DEMO "Build basic memory demonstration" OFF)
option(BUILD_DESIGN_CONCEPT_DEMO "Build design concept demonstration" OFF)
option(BUILD_VARIANT_AND_OPTIONAL "Build Variant and Optional demonstration" OFF)

add_executable(${PROGRAM} ${SOURCE_DIR}/main.cpp)
target_compile_features(${PROGRAM} PRIVATE cxx_std_20)

if(${BUILD_BITWISE_DEMO})
    message(STATUS "Preparting to build bitwise demo...")
    target_compile_definitions(${PROGRAM} PRIVATE USE_BITWISE_DEMO)
endif()

if(${BUILD_VARIANT_AND_OPTIONAL})
    message(STATUS "Preparting to build Variant and Optional demo...")
    target_compile_definitions(${PROGRAM} PRIVATE USE_VARIANT_OPTIONAL_DEMO)
endif()

if(${BUILD_DESIGN_CONCEPT_DEMO})
    message(STATUS "Preparting to build design concept demo...")
    target_compile_definitions(${PROGRAM} PRIVATE USE_DESIGN_CONCEPT_DEMO)
endif()

if(${BUILD_VECTOR_DEMO})
    message(STATUS "Preparting to build vector demo...")
    target_compile_definitions(${PROGRAM} PRIVATE USE_VECTOR_DEMO)
endif()

if(${BUILD_LAMBDA_DEMO})
    message(STATUS "Preparting to build lambda demo...")
    target_compile_definitions(${PROGRAM} PRIVATE USE_LAMBDA_DEMO)
endif()

if(${BUILD_MAP_DEMO})
    message(STATUS "Preparting to build map demo...")
    target_compile_definitions(${PROGRAM} PRIVATE USE_MAP_DEMO)
endif()

if(${BUILD_BASIC_MEMORY_DEMO})
    message(STATUS "Preparting to build basic memory demo...")
    target_compile_definitions(${PROGRAM} PRIVATE USE_BASIC_MEMORY_DEMO)
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

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/core/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/design_concepts/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(external/STL)
add_subdirectory(external/core)
add_subdirectory(external/design_concepts)
list(APPEND INCLUDE_DIRS 
"include" 
"external/STL/include" 
"external/core/include"
"external/design_concepts/include")

target_include_directories(${PROGRAM} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROGRAM} PRIVATE STL_Lib PRIVATE core_lib PRIVATE design_concept_lib)

