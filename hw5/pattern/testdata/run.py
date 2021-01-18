#!/usr/bin/env python3

import os


def main():
    """ main function """
    os.system('qemu-riscv64 ../../run_and_main/a.out')


if __name__ == '__main__':
    main()
