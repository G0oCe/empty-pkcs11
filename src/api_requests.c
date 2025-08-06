#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "api_requests.h"

static const char* BASE_URL = "http://localhost:5000";

char* api_build_get_slots_url(void) {
    const char* path = "/Slot";

    char* full_url = malloc(strlen(BASE_URL) + strlen(path) + 1);
    if (!full_url) {
        return NULL;
    }

    strcpy(full_url, BASE_URL);
    strcat(full_url, path);

    return full_url;
}