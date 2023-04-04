cmake_minimum_required(VERSION 3.0.0)
project(engine VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

link_directories(${CMAKE_SOURCE_DIR}/lib)

find_package(OpenGL REQUIRED)

set(LIBS glfw3 opengl32 glew32 ImGui sfml-audio sfml-system FLAC freetype ogg openal32 vorbis vorbisenc vorbisfile)

set(Engine_HEADERS src/Buffers/
                   src/Graphics/
                   src/Utils/)

set(Engine_SOURCES main.cpp src/Graphics/window.cpp src/Utils/camera.cpp)

add_executable(engine ${Engine_SOURCES} bin/engine.rc)

target_link_libraries(engine ${LIBS})
target_include_directories(engine PRIVATE include/ ${Engine_HEADERS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})