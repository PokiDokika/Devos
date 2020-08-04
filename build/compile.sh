#!/bin/sh
# i'm a mess :(

CC=i686-elf-gcc
#AC=nasm
AC=i686-elf-as

CCFLAGS="-std=gnu2x -ffreestanding -O2 -Wall -Wextra -m32"
# ACFLAGS="-felf32"
ACFLAGS=""

SRC_DIR="../"
BUILD_DIR="../"
ISOWS_DIR="../os/"

C_SRC_FILES=($(find $SRC_DIR* -iname "*.c" -type f))
C_OBJ_FILES=($(find $SRC_DIR* -iname "*.c" -type f -printf "%f\n" | sed 's/.c/.o/g'))

ASM_SRC_FILES=($(find $SRC_DIR* -iname "*.asm" -type f))
ASM_OBJ_FILES=($(find $SRC_DIR* -iname "*.asm" -type f -printf "%f\n" | sed 's/.asm/.o/g'))

OBJ_FILES_LIST_STRING=""

LINKER_LOC=$SRC_DIR"link.ld"

for ((i=0; i<${#C_SRC_FILES[@]}; i++)); do
  echo "compiling ${C_SRC_FILES[$i]}..."
  EXTRA_FLAGS=""
  if [ ${C_SRC_FILES[$i]} = "../src/cpu/idt.c" ]; then
    EXTRA_FLAGS="-mgeneral-regs-only"
  fi
  $CC -c ${C_SRC_FILES[$i]} -o ${C_OBJ_FILES[$i]} $CCFLAGS $EXTRA_FLAGS
  OBJ_FILES_LIST_STRING=$OBJ_FILES_LIST_STRING" "${C_OBJ_FILES[$i]}
done

for ((i=0; i<${#ASM_SRC_FILES[@]}; i++)); do

  echo "compiling ${ASM_SRC_FILES[$i]}..."
  $AC $ACFLAGS ${ASM_SRC_FILES[$i]} -o ${ASM_OBJ_FILES[$i]}
  OBJ_FILES_LIST_STRING=$OBJ_FILES_LIST_STRING" "${ASM_OBJ_FILES[$i]}
done

echo "linking object files into a single binary file..."

$CC -T $LINKER_LOC -o $ISOWS_DIR'boot/kernel.bin' -ffreestanding -O2 -nostdlib $OBJ_FILES_LIST_STRING -lgcc

if grub-file --is-x86-multiboot $ISOWS_DIR'boot/kernel.bin'; then
  echo "multiboot verified, continuing"
else
  echo "image file is not multiboot, exiting"
  exit 1
fi

echo "cleaning up"
rm -rf $OBJ_FILES_LIST_STRING

echo "creating an iso file with grub"
grub-mkrescue -o $BUILD_DIR'devos.iso' $ISOWS_DIR

exit $?