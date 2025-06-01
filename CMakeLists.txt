cmake_minimum_required(VERSION 3.10)
project(Gong C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(gong
  main.c
  errors/errors.c
  lexer/lexer.c
)
