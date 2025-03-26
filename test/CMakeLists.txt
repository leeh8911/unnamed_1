cmake_minimum_required(VERSION 3.10)

enable_testing()

find_package(GTest)

if(NOT GTest_FOUND)
    include(FetchContent)
    # Download and unpack googletest at configure time
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.11.0.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
else()
    include_directories(${GTEST_INCLUDE_DIRS})
endif()


set(TEST_FILES 
    domain/test_config.cpp
    domain/test_registry.cpp
)

add_executable(${PROJECT_TEST} test_main.cpp ${TEST_FILES})
target_include_directories(
    ${PROJECT_TEST} PRIVATE
    ${PROJECT_SOURCE_DIR}/include    
)
target_link_libraries(${PROJECT_TEST} GTest::GTest GTest::Main pthread ${PROJECT_LIB})

add_test(NAME MyTests COMMAND ${PROJECT_TEST})