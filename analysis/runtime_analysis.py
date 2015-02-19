import subprocess as sp
import matplotlib.pyplot as plt
import os
import numpy as np
import collections

working_dir = os.getcwd()

def fin():
    sp.call("cd " + working_dir, shell=True);

def make():
    cd_top = "cd \"$(git rev-parse --show-toplevel)\""
    make = "make clean && make"
    ret = "cd ./analysis"
    cmd = cd_top + " && " + make + " && " + ret
    sp.call(cmd, shell=True);

def run_order(n):
    p = sp.Popen("$(git rev-parse --show-toplevel)/main.exe " + str(n),
                 shell=True, stdout=sp.PIPE, stderr=sp.PIPE)
    p.wait()
    if p.returncode is not 0:
        print p.stderr.read()

    data = {}

    for line in p.stdout:
        words = line.split()
        data[words[0]] = float(words[1])/(100*float(4**n))

    return data


def plot_data(data):
    xs = data.keys()
    method_names = data[xs[0]].keys()
    ys = collections.defaultdict(list)
    for x in xs:
        for method in method_names:
            ys[method].append(data[x][method])

    fig = plt.figure()
    for method in method_names:
        print xs
        print ys[method]
        plt.plot(xs,ys[method])

    plt.yscale('log')
    plt.xlabel('Hilbert Curve Order')
    plt.ylabel('log(verification time)')
    plt.show()


def main():
    make()
    data = {}
    for order in range(1,13):
        data[order] = run_order(order)
    plot_data(data)
    fin()

main()
