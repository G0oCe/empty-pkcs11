#ifndef SLOT_PARSER_H
#define SLOT_PARSER_H

#include "slot_manager.h" // Убедитесь, что этот файл определяет SlotCache
#include "pkcs11.h"
// Парсит JSON-строку и заполняет структуру SlotCache.
// В случае успеха возвращает CKR_OK.
CK_RV parse_slot_json(const char* json_string, SlotCache* pCache);

#endif // SLOT_PARSER_H