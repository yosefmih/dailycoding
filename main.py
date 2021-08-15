#!/usr/bin/env python3

import os
import argparse 
import subprocess

func_to_file = {
    "find_smallest_number" : "findsmallestpositive.c",
    "bitarray": "bitarray.c",
    "fixed_point_array": "fixed_point_array.c",
    "merge_binary_trees": "merge_binary_trees.c"
}

def compile_and_run(func_file, args=[]):
    directory = os.path.dirname(os.path.realpath(__file__))
    p = subprocess.run(["gcc", func_file, "-o", "a.out"], cwd=directory)
    if p.returncode == 0:
        r = subprocess.run(['./a.out']  + args, capture_output=True, cwd=directory)
        if r.returncode == 0:
            print(r.stdout.decode('utf-8'), end="")
        else:
            print(r.stderr.decode('utf-8'), emd="")
    else:
        print("Was unable to compilee " + func_file)

def parse_args():
    parser = argparse.ArgumentParser("Dailycoding exercises")
    parser.add_argument(dest="func_name", type=str, choices=list(func_to_file.keys()), help="the function to run")
    parser.add_argument(dest="args", nargs="*", type=str, help="arguments to the function")
    return parser.parse_args()

if __name__ == '__main__':
    args = parse_args()
    file_for_func = func_to_file.get(args.func_name, "")
    if file_for_func == "":
        print("The chosen function doesn't exist. The functions available are " + str([i for i in func_to_file.keys()]))
    compile_and_run(file_for_func, args.args)