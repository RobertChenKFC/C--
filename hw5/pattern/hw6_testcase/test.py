#!/usr/bin/env python3

import os
import sys


def main():
    """ main function """

    use_gcc = False
    for arg in sys.argv[1:]:
        if arg == '--use-gcc':
            use_gcc = True
            continue

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
    int x;
    scanf("%d", &x);
    return x;
}

float fread() {
    float x;
    scanf("%f", &x);
    return x;
}
        '''

        with open(arg, 'r') as f:
            code = f.read()
            s += code

        s += '''
int main() {
    return MAIN();
}
        '''

        with open('TEMP_FILE.cpp', 'w') as f:
            f.write(s)

        filename, _ = os.path.splitext(arg)
        if use_gcc:
            os.system('g++ -o TEMP_FILE TEMP_FILE.cpp')
        else:
            os.system(
                'riscv64-unknown-linux-gnu-g++ -o TEMP_FILE TEMP_FILE.cpp -static')

        if code.find('read()') != -1:
            print(f'{arg} uses read/fread, skipping file')
            continue
        if use_gcc:
            os.system(f'./TEMP_FILE > {filename}.output')
        else:
            os.system(f'qemu-riscv64 TEMP_FILE > {filename}.output')


if __name__ == '__main__':
    main()
