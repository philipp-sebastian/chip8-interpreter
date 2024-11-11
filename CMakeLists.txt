cmake_minimum_required(VERSION 3.27)

project(chip8-interpreter C)

set(CMAKE_C_STANDARD 11)

# Finde alle C- und Header-Dateien in den Verzeichnissen
file(GLOB SOURCES "src/*.c" "include/*.h")

# Erstelle das ausführbare Programm
add_executable(Chip8-Interpreter ${SOURCES})