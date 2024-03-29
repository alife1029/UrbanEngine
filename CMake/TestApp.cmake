project(TestApp VERSION 1.0.0)

file(GLOB TEST_APP_SOURCES 
        ${TEST_APP_DIR}/src/**.c
        ${TEST_APP_DIR}/src/**.cpp
        ${TEST_APP_DIR}/src/**.h
        ${TEST_APP_DIR}/src/**.hpp
        )

add_executable(${PROJECT_NAME} ${TEST_APP_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${TEST_APP_LINKS})
target_include_directories(${PROJECT_NAME} PRIVATE ${TEST_APP_INCLUDES})

add_custom_command( TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${TEST_APP_DIR}/data ${CMAKE_BINARY_DIR}/data
                    )
