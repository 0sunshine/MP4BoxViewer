cmake_minimum_required(VERSION 3.5.0)
project(mp4box)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE BoxHeaders LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE BoxSources LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

message("mp4box header: ")
foreach(item IN LISTS BoxHeaders)
    message("   ${item}")
endforeach()

message("mp4box src: ")
foreach(item IN LISTS BoxSources)
    message("   ${item}")
endforeach()

add_library(${PROJECT_NAME} OBJECT ${BoxHeaders} ${BoxSources})

