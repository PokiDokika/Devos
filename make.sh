mkdir tmp

~/Documents/i686-elf-4.9.1-Linux-x86_64/bin/i686-elf-as boot.asm -o tmp/boot.o
~/Documents/i686-elf-4.9.1-Linux-x86_64/bin/i686-elf-gcc -c kernel.c -o tmp/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
~/Documents/i686-elf-4.9.1-Linux-x86_64/bin/i686-elf-gcc -T link.ld -o os/boot/kernel.bin -ffreestanding -O2 -nostdlib tmp/boot.o tmp/kernel.o -lgcc

rm -rf tmp
grub-mkrescue -o os.iso os/ 
