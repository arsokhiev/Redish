cmake_minimum_required(VERSION 3.2)

set(SERVER_PROJECT_NAME RedishServer)

set(SERVER_PUBLIC_INCLUDES
        include/Server.h
        include/ServerLog.h
        include/Utils.h
)

set(SERVER_PRIVATE_SOURCES
        src/Server.cpp
        src/ServerLog.cpp
        src/Utils.cpp
        src/ServerMain.cpp
)

add_executable(${SERVER_PROJECT_NAME} ${SERVER_PUBLIC_INCLUDES} ${SERVER_PRIVATE_SOURCES})

target_include_directories(${SERVER_PROJECT_NAME} PUBLIC include)
target_compile_features(${SERVER_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../vendor/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${SERVER_PROJECT_NAME} PRIVATE spdlog)