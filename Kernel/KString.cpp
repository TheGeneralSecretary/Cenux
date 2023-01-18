#include <Kernel/KString.h>

namespace Kernel
{
	size_t strlen(const char* s)
	{
		size_t len = 0;
		while (s[len]) len++;
		return len;
	}

	void strrev(char* s, uint32_t n)
	{
		for (uint32_t i = 0; i < n / 2; i++) {
			char tmp = s[i];
			s[i] = s[n - 1 - i];
			s[n - 1 - i] = tmp;
		}
	}

	void* memset(void* s, int32_t c, size_t n)
	{
		uint8_t* p1 = (uint8_t*)s;
		while (n--) *p1++ = c;
		return s;
	}

	void* memsetw(void* s, uint16_t c, size_t n)
	{
		uint16_t* p1 = (uint16_t*)s;
		while (n--) *p1++ = c;
		return s;
	}

	void* memcpy(void* d, const void* s, size_t n)
	{
		uint8_t* p1 = (uint8_t*)d;
		uint8_t* p2 = (uint8_t*)s;
		while (n--) *p1++ = *p2++;
		return d;
	}
}
