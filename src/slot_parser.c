#include "slot_parser.h"
#include <stdio.h>
#include <json-c/json.h>


// Вспомогательная структура, которая должна быть определена где-то еще,
// например в slot_manager.h

typedef struct {
    CK_SLOT_ID* pSlotIDs;
    CK_ULONG ulCount;
} SlotCache;


CK_RV parse_slot_json(const char* json_string, SlotCache* pCache) {
    if (!json_string || !pCache) {
        return CKR_ARGUMENTS_BAD;
    }

    // Инициализируем кэш
    pCache->pSlotIDs = NULL;
    pCache->ulCount = 0;

    json_object *parsed_json = json_tokener_parse(json_string);
    if (!parsed_json) {
        fprintf(stderr, "Error: Failed to parse JSON string.\n");
        return CKR_GENERAL_ERROR; // Или другая ошибка, например, CKR_DEVICE_DATA_INVALID
    }

    // Убедимся, что корневой элемент - это массив
    if (json_object_get_type(parsed_json) != json_type_array) {
        fprintf(stderr, "Error: JSON is not an array.\n");
        json_object_put(parsed_json); // Освобождаем память
        return CKR_GENERAL_ERROR;
    }

    size_t n_slots = json_object_array_length(parsed_json);
    if (n_slots == 0) {
        json_object_put(parsed_json);
        return CKR_OK; // Массив пуст, это не ошибка
    }

    pCache->ulCount = (CK_ULONG)n_slots;
    pCache->pSlotIDs = calloc(n_slots, sizeof(CK_SLOT_ID));

    if (!pCache->pSlotIDs) {
        json_object_put(parsed_json);
        return CKR_HOST_MEMORY;
    }

    // Проходим по всем элементам массива
    for (size_t i = 0; i < n_slots; i++) {
        json_object *slot_obj = json_object_array_get_idx(parsed_json, i);
        json_object *slot_id_obj;

        // Ищем в каждом объекте ключ "slotId"
        if (json_object_object_get_ex(slot_obj, "slotId", &slot_id_obj)) {
            // Преобразуем значение в число и сохраняем
            pCache->pSlotIDs[i] = (CK_SLOT_ID)json_object_get_int(slot_id_obj);
        } else {
            // Если в каком-то объекте нет нужного ключа, считаем данные некорректными
            fprintf(stderr, "Error: 'slotId' key not found in JSON object at index %zu\n", i);
            free(pCache->pSlotIDs);
            pCache->pSlotIDs = NULL;
            pCache->ulCount = 0;
            json_object_put(parsed_json);
            return CKR_GENERAL_ERROR;
        }
    }

    json_object_put(parsed_json); // Освобождаем память, выделенную парсером
    return CKR_OK;
}