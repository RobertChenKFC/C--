#!/usr/bin/env python3

import os
import sys


def main():
    """ main function """

    use_gcc = False
    skip_long_long_jump = False
    for arg in sys.argv[1:]:
        if arg == '--use-gcc':
            use_gcc = True
            continue
        if arg == '--skip-long-long-jump':
            skip_long_long_jump = True
            continue

        if skip_long_long_jump and arg == 'long-long-jump.c':
            continue

        print(f'checking {arg}')
        filename, _ = os.path.splitext(arg)
        if not os.path.exists(f'{filename}.output'):
            if use_gcc:
                os.system(f'./test.py --use-gcc {arg}')
            else:
                os.system(f'./test.py {arg}')

        cmd = (
            'cd ../.. && \\\n' +
            f'./parser pattern/testdata/{arg} && \\' +
            '''
cd run_and_main && \\
riscv64-unknown-linux-gnu-gcc -O0 -static main.S''')
        os.system(cmd)

        with open(arg, 'r') as f:
            if f.read().find('read()') != -1:
                print(f'{arg} uses read/fread, skipping file')
                continue

        cmd = (
            '''cd ../../run_and_main && \\
qemu-riscv64 a.out > output.txt && \\\n''' +
            f'diff output.txt ../pattern/testdata/{filename}.output > ../pattern/testdata/{filename}.diff'
        )
        ret = os.system(cmd)
        if ret != 0:
            print(f'\u001b[31m{arg} failed\u001b[0m')
            os.system(f'cat {filename}.diff')


if __name__ == "__main__":
    main()
