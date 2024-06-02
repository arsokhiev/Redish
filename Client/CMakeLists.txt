cmake_minimum_required(VERSION 3.2)

set(CLIENT_PROJECT_NAME RedishClient)

set(CLIENT_PUBLIC_INCLUDES
        include/Client.h
        include/ClientLog.h
)

set(CLIENT_PRIVATE_SOURCES
        src/Client.cpp
        src/ClientLog.cpp
        src/ClientMain.cpp
)

add_executable(${CLIENT_PROJECT_NAME} ${CLIENT_PUBLIC_INCLUDES} ${CLIENT_PRIVATE_SOURCES})

target_include_directories(${CLIENT_PROJECT_NAME} PUBLIC include)
target_compile_features(${CLIENT_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../vendor/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${CLIENT_PROJECT_NAME} PRIVATE spdlog)