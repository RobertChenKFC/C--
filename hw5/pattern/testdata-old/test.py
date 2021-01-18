#!/usr/bin/env python3

import os
import sys

for arg in sys.argv[1:]:
  s = '''
  #include <stdio.h>

  void write(int x) {
    printf("%d", x);
  }

  void write(float x) {
    printf("%f", x);
  }

  void write(const char *x) {
    printf("%s", x);
  }

  int read() {
    //int x;
    //scanf("%d", &x);
    return 1381;
  }

  float fread() {
    //float x;
    //scanf("%f", &x);
    return -12.81;
  }

  '''

  with open(arg, 'r') as f:
    s += f.read()

  s += '''
  int main() {
    return MAIN();
  }
  '''

  with open('TEMP_FILE.cpp', 'w') as f:
    f.write(s)

  filename, _ = os.path.splitext(arg)
  os.system('riscv64-unknown-linux-gnu-g++ -o TEMP_FILE TEMP_FILE.cpp -static')
  os.system(f'qemu-riscv64 TEMP_FILE > {filename}.output')
  # DEBUG
  #os.system('rm TEMP_FILE TEMP_FILE.cpp')

