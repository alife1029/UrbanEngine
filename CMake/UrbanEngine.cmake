project(UrbanEngine VERSION 1.0.0)

# HLSL Shaders For Direct3D 11
if(WIN32)
    add_custom_target(shaders)
    # Set HLSL shader sources
    set(HLSL_SOURCES
            ${URBAN_DIR}/shader/d3d/Solid2DVS.hlsl
            ${URBAN_DIR}/shader/d3d/Solid2DPS.hlsl
            )

    # Set HLSL shader properties
    set_source_files_properties(${URBAN_DIR}/shader/d3d/Solid2DVS.hlsl PROPERTIES ShaderType "vs")
    set_source_files_properties(${URBAN_DIR}/shader/d3d/Solid2DPS.hlsl PROPERTIES ShaderType "ps")
    set_source_files_properties(${HLSL_SOURCES} PROPERTIES ShaderModel "4_0")

    add_custom_command( TARGET shaders
                        COMMAND if not exist shaders mkdir shaders
                        COMMENT "Creating Shader Folder"
                        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                        )

    foreach(FILE ${HLSL_SOURCES})
        get_filename_component(FILE_WE ${FILE} NAME_WE)
        get_source_file_property(shadertype ${FILE} ShaderType)
        get_source_file_property(shadermodel ${FILE} ShaderModel)
        add_custom_command( TARGET shaders
                            COMMAND fxc.exe /nologo /Emain /T${shadertype}_${shadermodel} $<IF:$<CONFIG:DEBUG>,/Od,/O1> /Zi /Fo ${CMAKE_BINARY_DIR}/shaders/${FILE_WE}.cso /Fd ${CMAKE_BINARY_DIR}/shaders/${FILE_WE}.pdb ${FILE}
                            MAIN_DEPENDENCY ${FILE}
                            COMMENT "HLSL ${FILE}"
                            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                            VERBATIM
                            )
    endforeach(FILE)
endif()

list(APPEND URBAN_INCLUDES 
        ${URBAN_DIR}/src
        ${URBAN_DIR}/vendor/glm
        ${URBAN_DIR}/vendor/glad/include
        )

list(APPEND URBAN_LINKS 
        glad
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

if(WIN32)
    add_dependencies(${PROJECT_NAME} shaders)
endif()

list(APPEND TEST_APP_LINKS ${PROJECT_NAME})
list(APPEND TEST_APP_INCLUDES 
            ${URBAN_DIR}/src 
            ${URBAN_DIR}/vendor/glm
            )
