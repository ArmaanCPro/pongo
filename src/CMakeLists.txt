cmake_minimum_required(VERSION 3.28)

project(main)

if (MSVC)
    add_compile_options(/MP /EHsc /Zi)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(main
        main.cpp
        shader.h
        shader.cpp
        window.h
        window.cpp
        renderer.h
        renderer.cpp
        game.h
        game.cpp
        paddle.h
        paddle.cpp
        settings.h
        ball.cpp
        ball.h
        renderable.h
        mesh.cpp
        mesh.h
        material.cpp
        material.h
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

find_package(CMakeRC CONFIG REQUIRED)
cmrc_add_resource_library(shaders-resources
        ALIAS shaders::rc
        NAMESPACE shaders
        vertex.glsl
        fragment.glsl
)

target_link_libraries(main
    PRIVATE
        glfw
        glad::glad
        glm::glm-header-only
        shaders::rc
)
