cmake_minimum_required(VERSION 3.12)
project(Projeto_AEDA)

set(CMAKE_CXX_STANDARD 14)

include_directories("Projeto AEDA")

add_executable(Projeto_AEDA
        "Projeto AEDA/empresa.cpp"
        "Projeto AEDA/empresa.h"
        "Projeto AEDA/main.cpp"
        "Projeto AEDA/objetos.cpp"
        "Projeto AEDA/menu.cpp"
        "Projeto AEDA/objetos.h" "Projeto AEDA/menu.h" "Projeto AEDA/timing.h" "Projeto AEDA/timing.cpp" "Projeto AEDA/exceptions.cpp" "Projeto AEDA/exceptions.h" "Projeto AEDA/comparators.h")
