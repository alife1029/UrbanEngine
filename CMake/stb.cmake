project(stb)
add_library(${PROJECT_NAME} ${URBAN_DIR}/vendor/stb/src/stb_image.c)
target_include_directories(${PROJECT_NAME} PRIVATE ${URBAN_DIR}/vendor/stb/include)
