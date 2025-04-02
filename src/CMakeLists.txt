cmake_minimum_required(VERSION 3.28)

project(main)

if (MSVC)
    add_compile_options(/MP)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(main
    main.cpp
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
target_link_libraries(main
    PRIVATE
        glfw
        glad::glad
        glm::glm
)
