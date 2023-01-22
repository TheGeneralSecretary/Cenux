#include <Kernel/Drivers/VGA.h>
#include <Kernel/KPrintf.h>
#include <Kernel/KPanic.h>
#include <Kernel/CPU/GDT/GDT.h>
#include <Kernel/CPU/Interrupts/IDT.h>
#include <Kernel/CPU/Interrupts/Interrupt.h>
#include <Kernel/CPU/Interrupts/PIC.h>
#include <Kernel/Memory/KMem.h>
#include <Kernel/CPU/CPU.h>

namespace Kernel
{
	void InitKernel()
	{
		if (Drivers::VGA::Init() != 0)
			KPanic("Failed To Initialize VGA Driver\n");

		if (CPU::GDT::Init() != 0)
			KPanic("Failed To Initialize GDT\n");

		if (KMemInit() != 0)
			KPanic("Failed to Initialize KMem\n");

		if (CPU::IDT::Init() != 0)
			KPanic("Failed to Initialize IDT\n");

		if(CPU::PICRemap() != 0)
			KPanic("Failed to Remap PIC\n");

		CPU::EnableInterrupts();

		KPrintf("Kernal Successfully Initialized!\n");
	}
}

extern "C" void KMain()
{
	Kernel::InitKernel();
}
