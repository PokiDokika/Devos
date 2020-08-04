#!/bin/sh

if ./compile.sh; then
    ./qemu.sh
fi