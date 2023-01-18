#include <Kernel/KStdLib.h>
#include <Kernel/KString.h>

namespace Kernel
{
	int32_t itoa(int32_t n, char* buf, uint32_t len, uint32_t base)
	{
		uint32_t i = 0;
		uint8_t neg = 0;

		if (len == 0)
			return -1;

		if (n == 0) {
			buf[i] = '0';
			buf[++i] = '\0';
			return 0;
		}

		if (n < 0 && base == 10) {
			neg = 1;
			n = -n;
		}

		while (n != 0 && i < len) {
			int rem = n % base;
			buf[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
			n /= base;
		}

		if (neg)
			buf[i++] = '-';

		buf[i] = '\0';

		strrev(buf, i);

		return 0;
	}

	int32_t ctoi(char c)
	{
		return c - 48;
	}
}
