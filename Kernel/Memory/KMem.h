#pragma once

#include <stdint.h>

namespace Kernel
{
	int32_t KMemInit();
	uint32_t* KMalloc(uint32_t size);
	uint32_t* KZAlloc(uint32_t size);
	void KFree(uint32_t* ptr);
}
