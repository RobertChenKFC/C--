#!/usr/bin/env python3

import os
import sys

for arg in sys.argv[1:]:
  print(f'checking {arg}')
  with open(arg, 'r') as f:
    if f.read().find('read()') != -1:
      print(f'{arg} uses read/fread, skipping file')
      continue
      
  filename, _ = os.path.splitext(arg)
  cmd = (
    'cd ../.. && \\\n' +
    f'./parser pattern/testdata/{arg} && \\' +
    '''
cd run_and_main && \\
riscv64-unknown-linux-gnu-gcc -O0 -static main.S && \\
qemu-riscv64 a.out > output.txt && \\\n''' +
    f'diff output.txt ../pattern/testdata/{filename}.output > ../pattern/testdata/{filename}.diff'
  )
  ret = os.system(cmd)
  if ret != 0:
    print(f'{arg} failed')

