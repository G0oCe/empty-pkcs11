//
// Created by goose on 7/8/25.
//

#ifndef PKCS11_DRIVER_UTILS_H
#define PKCS11_DRIVER_UTILS_H
#include "empty-pkcs11.h" // Для типа CK_UTF8CHAR_PTR
#include <stddef.h>  // Для типа size_t

/**
 * @brief Заполняет строку байтов указанной длины, дополняя остаток пробелами.
 * * @param dest Указатель на буфер назначения.
 * @param src Исходная строка (null-terminated).
 * @param dest_size Полный размер буфера назначения.
 */
void fill_padded_string(CK_UTF8CHAR_PTR dest, const char* src, size_t dest_size);

// Сюда можно будет добавлять другие вспомогательные функции в будущем

#endif //PKCS11_DRIVER_UTILS_H
