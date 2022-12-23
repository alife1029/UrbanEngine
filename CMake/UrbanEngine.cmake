project(UrbanEngine VERSION 1.0.0)

list(APPEND URBAN_INCLUDES 
        ${URBAN_DIR}/src
        ${URBAN_DIR}/vendor/glm
        )

file(GLOB URBAN_SOURCES
            ${URBAN_DIR}/src/**.cpp
            ${URBAN_DIR}/src/UrbanEngine/**.cpp
            ${URBAN_DIR}/src/UrbanEngine/Application/**.cpp
            ${URBAN_DIR}/src/UrbanEngine/Graphics/**.cpp
            )

if (WIN32)
    file(GLOB URBAN_WIN32_SRCS
                ${URBAN_DIR}/src/UrbanEngine/Platform/Win32/**.cpp
                ${URBAN_DIR}/src/UrbanEngine/Platform/DirectX/**.cpp
                )
    list(APPEND URBAN_SOURCES ${URBAN_WIN32_SRCS})
endif()

add_library(${PROJECT_NAME} ${URBAN_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${URBAN_INCLUDES})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${URBAN_DIR}/src/urbanpch.h)

list(APPEND TEST_APP_LINKS ${PROJECT_NAME})
list(APPEND TEST_APP_INCLUDES 
            ${URBAN_DIR}/src 
            ${URBAN_DIR}/vendor/glm
            )
