cmake_minimum_required(VERSION 3.20)
project(Voxel)

#libraries
add_library(core
    src/core/file.c
    src/core/vector.c
)

add_library(game
    src/game/camera.c
)

add_library(platform
    src/platform/input.c
    src/platform/settings.c
    src/platform/gameState.c
    src/platform/window.c
)

add_library(gpu
    src/gpu/gpuDebug.c
    src/gpu/buffer.c
    src/gpu/shader.c
    src/gpu/texture.c
)

add_library(render
    src/render/renderer.c
)

#external libraries
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

#link libraries
target_include_directories(core PUBLIC src)
target_include_directories(game PUBLIC src)
target_include_directories(platform PUBLIC src)
target_include_directories(gpu PUBLIC src)
target_include_directories(render PUBLIC src)

target_link_libraries(gpu PRIVATE OpenGL::GL GLEW::GLEW core)
target_link_libraries(platform PUBLIC core PRIVATE gpu SDL2::SDL2)
target_link_libraries(game PRIVATE core platform m) # m = libm (or math.h)
target_link_libraries(render PRIVATE OpenGL::GL GLEW::GLEW gpu platform game)
#Some libraries may include: OpenGL::GL GLEW::GLEW SDL2::SDL2

#executables
add_executable(voxel
    src/app/main.c
)

target_include_directories(voxel PUBLIC src)
target_link_libraries(voxel PRIVATE
    core
    game
    platform
    gpu
    render
)