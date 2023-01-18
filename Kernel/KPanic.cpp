#include <Kernel/KPanic.h>
#include <Kernel/KPrintf.h>

namespace Kernel
{
	void KPanic(const char* s)
	{
		KPrintf(s);
		while (true) {}
	}
}
