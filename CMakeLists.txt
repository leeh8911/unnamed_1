cmake_minimum_required(VERSION 3.22)

project(RegistryProject)
set(PROJECT_LIB ${PROJECT_NAME}_lib)
set(PROJECT_TEST ${PROJECT_NAME}_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_TESTING "Build the testing tree" ON)

# 필요한 라이브러리 찾기
find_package(nlohmann_json CONFIG REQUIRED)
find_package(yaml-cpp REQUIRED)

set(SRC_FILES
    src/domain/config/parser/config_parser.cpp
)

add_library(${PROJECT_LIB} ${SRC_FILES})
target_include_directories(${PROJECT_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_LIB} PUBLIC 
    nlohmann_json::nlohmann_json
    yaml-cpp
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC 
    ${PROJECT_LIB} 
    nlohmann_json::nlohmann_json
    yaml-cpp
)

if(BUILD_TESTING)
    message(STATUS "Building tests")
    add_subdirectory(test)
endif(BUILD_TESTING)
