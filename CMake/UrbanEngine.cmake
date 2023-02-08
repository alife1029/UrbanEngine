project(UrbanEngine VERSION 1.0.0)

list(APPEND URBAN_INCLUDES 
        ${URBAN_DIR}/src
        ${URBAN_DIR}/vendor/glm
        ${URBAN_DIR}/vendor/glad/include
        ${URBAN_DIR}/vendor/stb/include
        )

list(APPEND URBAN_LINKS 
        glad
        stb
        )

file(GLOB URBAN_SOURCES
            ${URBAN_DIR}/src/**.cpp
            ${URBAN_DIR}/src/**.hpp
            ${URBAN_DIR}/src/**.h
            ${URBAN_DIR}/src/UrbanEngine/**.cpp
            ${URBAN_DIR}/src/UrbanEngine/**.hpp
            ${URBAN_DIR}/src/UrbanEngine/**.h
            ${URBAN_DIR}/src/UrbanEngine/Application/**.cpp
            ${URBAN_DIR}/src/UrbanEngine/Application/**.hpp
            ${URBAN_DIR}/src/UrbanEngine/Application/**.h
            ${URBAN_DIR}/src/UrbanEngine/Graphics/**.cpp
            ${URBAN_DIR}/src/UrbanEngine/Graphics/**.hpp
            ${URBAN_DIR}/src/UrbanEngine/Graphics/**.h

            ${URBAN_DIR}/src/UrbanEngine/Platform/OpenGL/**.cpp
            ${URBAN_DIR}/src/UrbanEngine/Platform/OpenGL/**.hpp
            ${URBAN_DIR}/src/UrbanEngine/Platform/OpenGL/**.h
            )

if (WIN32)
    file(GLOB URBAN_WIN32_SRCS
                ${URBAN_DIR}/src/UrbanEngine/Platform/Win32/**.cpp
                ${URBAN_DIR}/src/UrbanEngine/Platform/Win32/**.h
                ${URBAN_DIR}/src/UrbanEngine/Platform/Win32/**.hpp
                ${URBAN_DIR}/src/UrbanEngine/Platform/DirectX/**.cpp
                ${URBAN_DIR}/src/UrbanEngine/Platform/DirectX/**.h
                ${URBAN_DIR}/src/UrbanEngine/Platform/DirectX/**.hpp
                )
    list(APPEND URBAN_SOURCES ${URBAN_WIN32_SRCS})
endif()

add_library(${PROJECT_NAME} ${URBAN_SOURCES})

target_link_libraries(${PROJECT_NAME} ${URBAN_LINKS})
target_include_directories(${PROJECT_NAME} PRIVATE ${URBAN_INCLUDES})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${URBAN_DIR}/src/urbanpch.h)

# GLSL Shaders For OpenGL
add_custom_command( TARGET ${PROJECT_NAME} PRE_BUILD 
                    COMMAND if not exist shaders mkdir shaders
                    COMMENT "Creating Shader Folder"
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}                    
                    )
add_custom_command( TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${URBAN_DIR}/shader/glsl/
                    ${CMAKE_BINARY_DIR}/shaders/
                    )

# HLSL Shaders For Direct3D 11
if(WIN32)
    # Set HLSL shader sources
    file(GLOB HLSL_VS_SOURCES ${URBAN_DIR}/shader/d3d/**VS.hlsl)
    file(GLOB HLSL_PS_SOURCES ${URBAN_DIR}/shader/d3d/**PS.hlsl)

    # Vertex shaders
    foreach (FILE ${HLSL_VS_SOURCES})
        get_filename_component(FILE_WE ${FILE} NAME_WE)
        add_custom_command( TARGET ${PROJECT_NAME} POST_BUILD
                            COMMAND fxc.exe /nologo /Emain /Tvs_4_0 $<IF:$<CONFIG:Debug>,/Od,/O1> /Zi /Fo ${CMAKE_BINARY_DIR}/shaders/${FILE_WE}.cso /Fd ${CMAKE_BINARY_DIR}/shaders/${FILE_WE}.pdb ${FILE}
                            COMMENT "HLSL ${FILE}"
                            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                            )
    endforeach(FILE)

    # Pixel shaders
    foreach (FILE ${HLSL_PS_SOURCES})
        get_filename_component(FILE_WE ${FILE} NAME_WE)
        add_custom_command( TARGET ${PROJECT_NAME} POST_BUILD
                            COMMAND fxc.exe /nologo /Emain /Tps_4_0 $<IF:$<CONFIG:Debug>,/Od,/O1> /Zi /Fo ${CMAKE_BINARY_DIR}/shaders/${FILE_WE}.cso /Fd ${CMAKE_BINARY_DIR}/shaders/${FILE_WE}.pdb ${FILE}
                            COMMENT "HLSL ${FILE}"
                            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                            )
    endforeach(FILE)
endif()

list(APPEND TEST_APP_LINKS ${PROJECT_NAME})
list(APPEND TEST_APP_INCLUDES 
            ${URBAN_DIR}/src 
            ${URBAN_DIR}/vendor/glm
            )
