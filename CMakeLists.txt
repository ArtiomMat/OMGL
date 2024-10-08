cmake_minimum_required(VERSION 3.25)
project(omgl)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The cross platform files
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Add the platform source files and append them
if(WIN32)
    set(LIBRARIES -lopengl32 -lws2_32 -lole32 -lcomctl32 -lgdi32)
    file(GLOB PLATFORM_SOURCES "${CMAKE_SOURCE_DIR}/src/win32/*.cpp")
elseif(UNIX)
    set(LIBRARIES -lGL)
    file(GLOB PLATFORM_SOURCES "${CMAKE_SOURCE_DIR}/src/unix/*.cpp")
endif()
list(APPEND SOURCES ${PLATFORM_SOURCES})

# Add an executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra ${PLATFORM_FLAGS})

target_link_options(${PROJECT_NAME} PRIVATE ${PLATFORM_LINKS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
