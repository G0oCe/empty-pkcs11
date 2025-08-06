#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

// Выполняет GET-запрос по указанному URL.
// Возвращает строку с ответом сервера, которую нужно освободить с помощью free().
// В случае ошибки возвращает NULL.
char* fetch_data_from_url(const char* url);

#endif // HTTP_CLIENT_H