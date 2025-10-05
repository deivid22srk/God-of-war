cmake_minimum_required(VERSION 3.22.1)

project("godofwar")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(native_app_glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

target_include_directories(native_app_glue PUBLIC
    ${ANDROID_NDK}/sources/android/native_app_glue)

add_library(${CMAKE_PROJECT_NAME} SHARED
    main.cpp
    vulkan_renderer.cpp
    game_engine.cpp
    camera.cpp
    player.cpp
    shaders.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue)

find_library(log-lib log)
find_library(android-lib android)

target_link_libraries(${CMAKE_PROJECT_NAME}
    native_app_glue
    ${log-lib}
    ${android-lib}
    vulkan
)
