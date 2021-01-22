#!/bin/bash
./parser $1
riscv64-unknown-elf-gcc -O0 -static main.S
./qemu-riscv64 a.out
