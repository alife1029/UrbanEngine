project(TestApp VERSION 1.0.0)

file(GLOB TEST_APP_SOURCES ${TEST_APP_DIR}/src/**.cpp)

add_executable(${PROJECT_NAME} ${TEST_APP_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${TEST_APP_LINKS})
target_include_directories(${PROJECT_NAME} PRIVATE ${TEST_APP_INCLUDES})
