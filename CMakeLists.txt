# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта и язык программирования (ИСПРАВЛЕНО НА C)
project(pkcs11_driver C)

# --- Поиск всех исходных и заголовочных файлов внутри папки src ---
file(GLOB_RECURSE PROJECT_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# --- Создание библиотеки ---
add_library(pkcs11_lib SHARED ${PROJECT_FILES})

# --- Настройка путей для заголовочных файлов ---
target_include_directories(pkcs11_lib PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cryptoki"
)

# --- Настройка свойств библиотеки ---
# (остальная часть файла остается без изменений)
set_target_properties(pkcs11_lib PROPERTIES OUTPUT_NAME "empty-pkcs11")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Configuring for 64-bit build")
    target_compile_options(pkcs11_lib PRIVATE -m64)
    set_target_properties(pkcs11_lib PROPERTIES SUFFIX "-x64.so")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(STATUS "Configuring for 32-bit build")
    target_compile_options(pkcs11_lib PRIVATE -m32)
    set_target_properties(pkcs11_lib PROPERTIES SUFFIX "-x86.so")
endif()