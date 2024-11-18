#This file is mostly the file Erik Yuzwa (https://gist.github.com/erikyuzwa) provides in his YouTube tutorial for SDL3 in CLion

cmake_minimum_required(VERSION 3.27)

project(chip8-interpreter C)

# Setze den C-Standard auf C11
set(CMAKE_C_STANDARD 11)

# Include the command that downloads libraries
include(FetchContent)

# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
    )
    FetchContent_MakeAvailable(${libName})
endfunction()

# add SDL3 support
find_package(SDL3 QUIET)
if (NOT SDL3_FOUND)
    message(STATUS "Getting SDL3 from Github")
    include_dependency(SDL3 https://github.com/libsdl-org/SDL.git preview-3.1.6)
else()
    message(STATUS "Using local SDL3")
endif()

# Suchpfade für Include- und Quell-Dateien
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES "src/*.c")

# Füge das ausführbare Programm hinzu
add_executable(chip8-interpreter ${SOURCES})

# SDL3-Header und -Libraries hinzufügen
target_include_directories(chip8-interpreter PUBLIC ${SDL3_INCLUDE_DIRS})
target_link_libraries(chip8-interpreter PRIVATE SDL3::SDL3)

# macOS-spezifische Einstellungen
if (APPLE)
    message(STATUS "Configuring for macOS")
    target_link_libraries(chip8-interpreter PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreAudio" "-framework CoreVideo")
endif()

# Windows-spezifische Einstellungen
if (WIN32)
    add_custom_command(
            TARGET chip8-interpreter POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:chip8-interpreter>"
            VERBATIM
    )
endif()

# Debugging aktivieren (optional)
set(CMAKE_BUILD_TYPE Debug)

# Compiler-Warnungen für C-Code
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(chip8-interpreter PRIVATE -Wall -Wextra -pedantic -Werror)
elseif(CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
    target_compile_options(chip8-interpreter PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()