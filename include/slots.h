#ifndef SLOTS_H
#define SLOTS_H

#include <pkcs11.h>

// Главная функция для обновления списка слотов.
CK_RV slots_refresh(void);

// Получение списка слотов (для вызова из C_GetSlotList).
CK_RV slots_get_list(CK_BBOOL tokenPresent, CK_SLOT_ID_PTR pSlotList, CK_ULONG_PTR pulCount);

// Очистка кэша при выходе.
void slots_cache_cleanup(void);

#endif // SLOTS_H