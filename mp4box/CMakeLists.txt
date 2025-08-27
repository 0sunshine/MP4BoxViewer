cmake_minimum_required(VERSION 3.5.0)
project(mp4box)

include_directories(./include)

file(GLOB BoxHeaders LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/include/*)
file(GLOB BoxSources LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

message("mp4box header: ")
foreach(item IN LISTS BoxHeaders)
    message("   ${item}")
endforeach()

message("mp4box src: ")
foreach(item IN LISTS BoxSources)
    message("   ${item}")
endforeach()

add_library(${PROJECT_NAME} OBJECT ${BoxHeaders} ${BoxSources})

