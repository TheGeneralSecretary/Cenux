set auto-load safe-path .
set disassembly-flavor intel

add-symbol-file ./Build/KernelFull.o 0x00100000
break Kernel.cpp:KMain
target remote | qemu-system-i386 -hda ./Build/Cenux.bin -S -gdb stdio

define hook-stop
print/x $eax
print/x $ebx
print/x $ecx
print/x $edx
print $eflags
x/xw $esp

disassemble $eip, +10

end
