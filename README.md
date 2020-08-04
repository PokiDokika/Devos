# Devos
An experimental operating system

### Building

The only dependencies you need are a i686-elf toolchain and a cross-compiler for that target.
Modify `build/compile.sh` if needed, and run it. `build/compile_run.sh` will run `build/qemu.sh` if `build/compile.sh` succeeds.
It'll automatically make an ISO image in the specified build directory in the script.