cmake_minimum_required(VERSION 3.15)
project(CRUD_Desenvolvedores C)

set(CMAKE_C_STANDARD 11)  # Define a versão do C como C11

# Adicionando o diretório correto onde o arquivo `main.c` se encontra
add_executable(CRUD_Desenvolvedores C/main.c)

# Definir que o diretório de compilação do executável é na pasta C
set_target_properties(CRUD_Desenvolvedores PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/C
)
