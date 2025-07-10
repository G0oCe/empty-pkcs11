//
// Created by goose on 7/8/25.
//
#include "utils.h"   // Подключаем собственный заголовок
#include <string.h>  // Для memset, memcpy, strlen

/**
 * Заполняет буфер строкой с дополнением пробелами (\0 обязателен).
 * @param dest          Буфер назначения (размер >= dest_size + 1, включая \0).
 * @param src           Исходная строка (гарантированно нуль-терминирована).
 * @param dest_size     Максимальное число символов (без учёта \0).
 * @return              Число скопированных символов.
 */
size_t fill_padded_string_fast(
        CK_UTF8CHAR_PTR dest,
        const char* src,
        size_t dest_size
) {

    if (!dest || !src) {
        return 0;  // Незнаю будет ли это правильно работать
    }

    // Копируем данные и добавляем пробелы
    size_t src_len = strlen(src);
    size_t copy_len = (src_len < dest_size) ? src_len : dest_size;

    memset(dest, ' ', dest_size);  // Заполняем пробелами
    memcpy(dest, src, copy_len);   // Копируем строку
    dest[dest_size] = '\0';

    return copy_len;
}