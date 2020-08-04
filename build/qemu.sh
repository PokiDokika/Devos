#!/bin/sh

# grub bork
qemu-system-x86_64 -gdb tcp::9000 -soundhw pcspk -cdrom ../devos.iso -serial stdio -enable-kvm -cpu host