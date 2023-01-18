#include <Kernel/Drivers/VGA.h>
#include <Kernel/KPrintf.h>
#include <Kernel/KPanic.h>
#include <Kernel/CPU/GDT/GDT.h>

namespace Kernel
{
	void InitKernel()
	{
		if (Drivers::VGA::Init() != 0)
			KPanic("Failed To Initialize VGA Driver\n");

		if (CPU::GDT::Init() != 0)
			KPanic("Failed To Initialize GDT");

		KPrintf("Kernal Successfully Initialized\n");
	}
}

extern "C" void KMain()
{
	Kernel::InitKernel();
}
