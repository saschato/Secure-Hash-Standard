cmake_minimum_required(VERSION 3.26)
project(Secure-Hash-Standard C)

set(CMAKE_C_STANDARD 11)

add_executable(Secure-Hash-Standard src/sha256/example.c
        src/sha256/sha256.c
)
