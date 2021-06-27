cmake_minimum_required(VERSION 3.20)

file(TIMESTAMP "${CMAKE_CURRENT_LIST_DIR}/vcpkg.json" vcpkg_json_timestamp)
if(VCPKG_JSON_TIMESTAMP_PREV STREQUAL vcpkg_json_timestamp)
    set(VCPKG_MANIFEST_INSTALL OFF CACHE STRING "" FORCE)
else()
    set(VCPKG_MANIFEST_INSTALL ON CACHE STRING "" FORCE)
endif()

project(activeobj LANGUAGES CXX)

set(VCPKG_JSON_TIMESTAMP_PREV "${vcpkg_json_timestamp}" CACHE STRING "" FORCE)

add_library(
  ${PROJECT_NAME} STATIC

  src/activeobj.cpp
)
add_library(pfaco::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(
  ${PROJECT_NAME}

  PUBLIC
    cxx_std_17
)

## Install headers
install(
    FILES
        include/activeobj/activeobj.h
     DESTINATION
        include/activeobj
)

install(
    TARGETS
        ${PROJECT_NAME}
    EXPORT
        ${PROJECT_NAME}Config
    LIBRARY 
        DESTINATION 
            lib
)

install(
    EXPORT
        ${PROJECT_NAME}Config
    NAMESPACE
        pfaco::
    DESTINATION
        share/${PROJECT_NAME}/
)
