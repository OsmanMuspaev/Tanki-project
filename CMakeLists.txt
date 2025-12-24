cmake_minimum_required(VERSION 3.16)
project(MyGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь, где CMake найдёт SFMLConfig.cmake
set(SFML_DIR /opt/homebrew/lib/cmake/SFML)

# Ищем SFML 3 и нужные компоненты
find_package(SFML 3 REQUIRED COMPONENTS Window Graphics System)

# Источники
file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# Подключаем CMake‑цели SFML
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SFML::Window
        SFML::Graphics
        SFML::System
)
