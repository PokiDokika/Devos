# Devos
An experimental operating system


### Building

#### Building a binary file
Check https://wiki.osdev.org/GCC_Cross-Compiler for a GCC Cross Compiler to build it

```i686-elf-4.9.1-Linux-x86_64/bin/i686-elf-as boot.asm -o boot.o
i686-elf-4.9.1-Linux-x86_64/bin/i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-4.9.1-Linux-x86_64/bin/i686-elf-gcc -T link.ld -o os/boot/kernel.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
```

#### Converting a binary file to an ISO
```grub-mkrescue -o os.iso os/```
