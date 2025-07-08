//
// Created by goose on 7/8/25.
//
#include "utils.h"   // Подключаем собственный заголовок
#include <string.h>  // Для memset, memcpy, strlen

// Обратите внимание: `static inline` здесь больше не нужны
void fill_padded_string(CK_UTF8CHAR_PTR dest, const char* src, size_t dest_size)
{
    memset(dest, ' ', dest_size);

    size_t src_len = strlen(src);
    if (src_len > dest_size) {
        src_len = dest_size;
    }
    memcpy(dest, src, src_len);
}