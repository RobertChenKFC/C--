#!/usr/bin/env python3

import argparse
import os

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description="generate png file containing AST of C-- code")
    parser.add_argument('input_file', metavar='input-file',
                        nargs='+', help='input C-- source code')

    args = parser.parse_args()
    input_files = args.input_file
    for input_file in input_files:
        print(f'generating png for {input_file}...')
        if os.system(f'./parser {input_file}') != 0:
            print(f'[Error] parser returned non-zero for {input_file}')
            continue
        filename, extenstion = os.path.splitext(input_file)
        os.system(f'mv AST_Graph.gv {filename}.gv')
        os.system(f'dot -Tpng {filename}.gv -o {filename}.png')
