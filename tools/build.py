#!/usr/bin/env python3

import argparse
from setup import get_build_dir
import subprocess
import os

def main():
    parser = argparse.ArgumentParser(
        'build.py', description="Build the Hagi decompilation project")
    parser.add_argument('--clean', action='store_true',
                        help="Clean before building")
    parser.add_argument('--verbose', action='store_true',
                        help="Give verbose output")
    args = parser.parse_args()

    if not get_build_dir().is_dir():
        print("Please run setup.py first.")
        exit(1)

    cmake_args = ['cmake', '--build', str(get_build_dir())]
    if args.clean:
        cmake_args.append('--clean-first')
    if args.verbose:
        os.environ['VERBOSE'] = '1'

    try:
        subprocess.run(cmake_args, check=True)
    except subprocess.CalledProcessError:
        exit(1)  # silently exit with failure if build failed

if __name__ == "__main__":
    main()
