#pragma once

#include <stdint.h>

namespace Kernel
{
	int32_t itoa(int32_t n, char* buf, uint32_t len, uint32_t base);
	int32_t ctoi(char c);
}
