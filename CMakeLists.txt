cmake_minimum_required(VERSION 3.27)

project(chip8-interpreter C)

# Setze den Standard auf C11
set(CMAKE_C_STANDARD 11)

# Suchpfade für Include- und Quell-Dateien
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES "src/*.c")

# Füge das ausführbare Programm hinzu
add_executable(Chip8-Interpreter ${SOURCES})

# macOS-spezifische Einstellungen
if(APPLE)
    # Linke gegen Frameworks, falls benötigt

endif()

# Debugging aktivieren (optional)
set(CMAKE_BUILD_TYPE Debug)

# Compiler-Warnungen
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(Chip8-Interpreter PRIVATE -Wall -Wextra -pedantic -Werror)
endif()