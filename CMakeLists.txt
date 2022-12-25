cmake_minimum_required(VERSION 3.5)

set(PROGRAM "CppDemo")
set(SOURCE_DIR "src")

project(${PROGRAM}
        VERSION 0.0.1
        DESCRIPTION "C++ demonstration app"
        LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "-Wall")

add_executable(${PROGRAM} ${SOURCE_DIR}/main.cpp)
target_compile_features(${PROGRAM} PRIVATE cxx_std_20)

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
list(APPEND INCLUDE_DIRS "include" "external/STL/include")

target_include_directories(${PROGRAM} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROGRAM} PRIVATE STL_Lib)

