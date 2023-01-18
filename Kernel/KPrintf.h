#pragma once

#include <stdint.h>
#include <stdarg.h>

namespace Kernel
{
	void KPrint(const char* str);
	void KPutChar(char c);
	int32_t KPrintf(const char* fmt, ...);
}
