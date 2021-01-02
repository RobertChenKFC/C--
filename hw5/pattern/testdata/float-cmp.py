#!/usr/bin/env python3

import os
import sys
import numpy

for arg in sys.argv[1:]:
  print(f'checking {arg}')
  with open(arg, 'r') as f:
    if f.read().find('read()') == 0:
      print(f'{arg} uses read/fread, skipping file')
      continue
      
  filename, _ = os.path.splitext(arg)
  cmd = (
    'cd ../.. && \\\n' +
    f'./parser pattern/testdata/{arg} && \\' +
    '''
cd run_and_main && \\
riscv64-unknown-linux-gnu-gcc -O0 -static main.S && \\
qemu-riscv64 a.out > output.txt'''
  )
  ret = os.system(cmd)
  if ret != 0:
    print(f'{arg} failed')

  l1 = []
  with open('../../run_and_main/output.txt', 'r') as f:
    l1 = [numpy.float32(x) for x in f.read().split()]
  l2 = []
  with open(f'{filename}.output', 'r') as f:
    l2 = [numpy.float32(x) for x in f.read().split()]

  if len(l1) != len(l2):
    print(f'{arg} failed: different output length ({len(l1)} != {len(l2)})')
  else:
    for i, (f1, f2) in enumerate(zip(l1, l2)):
      if f1 != f2:
        print(f'{arg} failed: {f1} != {f2} on line {i + 1}')

