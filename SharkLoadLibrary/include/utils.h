#ifndef UTILS_H
#define UTILS_H

#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")

struct MemoryStruct {
    char* memory;
    size_t size;
};

static size_t
WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp);

int wget(LPCWSTR url, struct MemoryStruct* chunk);

#endif // !UTILS_H
