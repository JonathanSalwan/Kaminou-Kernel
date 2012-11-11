Kaminou Kernel
==============

Juste a another kernel from scratch who's not finished...
Normally I had not want to release this project, but he is dying in a
folder. This project was just for understanding how works the kernel.

The kernel works only for x86 32 bits.


Installation
------------

    You need Bochs x86 Emulator (>=2.5.1)

    cd ./Kaminou-Kernel
    mkdir ./loop
    make
    make copy
    make run


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

