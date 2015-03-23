import subprocess as sp
import os
import collections
import time
import pickle

working_dir = os.getcwd()
NUM_REPITITIONS = 1000


def fin():
    sp.call("cd " + working_dir, shell=True)


def make():
    cd_top = "cd \"$(git rev-parse --show-toplevel)\""
    make = "make clean && make"
    ret = "cd ./analysis"
    cmd = cd_top + " && " + make + " && " + ret
    sp.call(cmd, shell=True)


def run_order(n):
    cmd = "$(git rev-parse --show-toplevel)/main.exe %d %d" \
          % (n, NUM_REPITITIONS)
    p = sp.Popen(cmd, shell=True, stdout=sp.PIPE, stderr=sp.PIPE)
    p.wait()
    if p.returncode is not 0:
        print p.stderr.read()

    data = {}

    for line in p.stdout:
        words = line.split()
        data[words[0]] = float(words[1])/(NUM_REPITITIONS*float(4**n))

    return data



def save_data(data):
    with open("performance-data-" + str(time.time()), 'w') as f:
        pickle.dump(data, f)


def main():
    make()
    data = {}
    for order in range(1, 13):
        data[order] = run_order(order)
    save_data(data)
    fin()


if __name__ == "__main__":
    main()
