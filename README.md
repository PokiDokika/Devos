# Devos
An experimental operating system

### Contributing
This project's goal is just to get an operating system made. It is merely a hobbyist project and the goal of it is to learn more about how operating systems work. Please feel free to contribute to the project by improving code, adding new functionalities or making anything that works.


### Building

The only dependencies you need are a i686-elf toolchain and a cross-compiler for that target.
Modify `build/compile.sh` if needed, and run it. `build/compile_run.sh` will run `build/qemu.sh` if `build/compile.sh` succeeds.
To build an ISO you need the following `libisoburn mtools` (grub-mkconfig is also needed but comes with grub)
It'll automatically make an ISO image in the specified build directory in the script.


### Goals
Just a list of things that would be nice to have in the OS but isn't done yet. (most likely due to lack of os theory)

- Support for hard disks (ATA probably)
- Actual commands that aren't baked in (loading binary files I guess)
- Support for other things than VGA
- 64-bit?
- (some) POSIX compliancy
