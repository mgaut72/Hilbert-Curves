import sys
import pickle
import collections
import matplotlib.pyplot as plt


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
        plt.plot(xs, ys[method])

    #plt.yscale('log')
    plt.xlabel('Hilbert Curve Order')
    plt.ylabel('log(verification time)')
    plt.show()

def load_data(fname):
    with open(fname, 'r') as f:
        return pickle.load(f)

def main():
    fname = sys.argv[1]
    data = load_data(fname)
    plot_data(data)

if __name__ == "__main__":
    main()
