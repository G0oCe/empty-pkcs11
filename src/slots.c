#include "slots.h"
#include "slot_manager.h"
#include "api_requests.h" // <-- Используем сборщик URL
#include "http_client.h"  // <-- Используем HTTP-клиент
#include "slot_parser.h"  // <-- Используем парсер

#include <stdio.h>
#include <stdlib.h>

#include "pkcs11.h"

// Наш кэш, видимый только внутри этого файла
static SlotCache g_slotCache = { NULL, 0 };

CK_RV slots_refresh(void) {
    CK_RV rv = CKR_OK;

    char* url = api_build_get_slots_url();
    if (!url) {
        return CKR_HOST_MEMORY;
    }

    char* json_data = fetch_data_from_url(url);
    free(url); // URL больше не нужен, освобождаем память

    if (!json_data) {
        return CKR_DEVICE_ERROR; // Ошибка сети или сервера
    }

    slots_cache_cleanup();
    rv = parse_slot_json(json_data, &g_slotCache);

    free(json_data); // Сырые JSON-данные больше не нужны

    if (rv == CKR_OK) {
        printf("Successfully refreshed %lu slots.\n", g_slotCache.ulCount);
    }

    return rv;
}

// Реализация получения списка (теперь она очень простая)
CK_RV slots_get_list(CK_BBOOL tokenPresent, CK_SLOT_ID_PTR pSlotList, CK_ULONG_PTR pulCount) {
    // TODO: Фильтрация по tokenPresent

    if (pSlotList == NULL) {
        *pulCount = g_slotCache.ulCount;
    } else {
        if (*pulCount < g_slotCache.ulCount) {
            return CKR_BUFFER_TOO_SMALL;
        }
        memcpy(pSlotList, g_slotCache.pSlotIDs, g_slotCache.ulCount * sizeof(CK_SLOT_ID));
        *pulCount = g_slotCache.ulCount;
    }
    return CKR_OK;
}

// Реализация очистки
void slots_cache_cleanup(void) {
    if (g_slotCache.pSlotIDs) {
        free(g_slotCache.pSlotIDs);
        g_slotCache.pSlotIDs = NULL;
    }
    g_slotCache.ulCount = 0;
}