#!/bin/bash
cd ..
./parser pattern/$1
cd run_and_main
riscv64-unknown-linux-gnu-gcc -O0 -static main.S
qemu-riscv64 a.out