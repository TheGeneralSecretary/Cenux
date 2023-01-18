#pragma once

#include <stdint.h>
#include <stddef.h>

namespace Kernel
{
	size_t strlen(const char* s);
	void strrev(char* s, uint32_t n);

	void* memset(void* s, int32_t c, size_t n);
	void* memsetw(void* s, uint16_t c, size_t n);
	void* memcpy(void* d, const void* s, size_t n);
}
