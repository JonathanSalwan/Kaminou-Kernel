Kaminou Kernel
==============

Just another (unfinished) kernel from scratch...
At first I didn't plan on releasing this project, but it's dying in a
directory. This project was just for understanding how the kernel works.

The kernel works only for x86 32 bits.


Installation
------------

    cd ./Kaminou-Kernel
    mkdir ./loop
    make
    make copy
    make run (Only with bochs)

Emu/Vm Tested
-------------

This 'mini-kernel' has been tested and works with vmware, bochs, qemu and virtualbox.
This kernel is compiled to Intel 32-bits architecture.

    Vmware 9.0.0.812388  : Create a new VM and set up the floppy image.
    Bochs 2.4.5	         : Use the bochsrc file
    Virtualbox 4.2.6     : Create a new VM and set up the floppy image.
    Qemu 1.2.2	         : qemu-system-i386 -fda ./floppy.img


Features supported
------------------

    - protected mode 32 bits
    - Ring 0
    - Ring 3
    - Multi process with simple scheduler (Multitasking)
    - Segmentation
    - Paging
    - Memory Allocation (it's sucks :P)
    - Choose custom Bootloader or Grub bootloader
    - Interrupts (keyboard, clock etc... (irq{0...7}))
    - CPU Exceptions (pagefault, zero div, etc...)
    - Syscalls

