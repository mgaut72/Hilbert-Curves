import collections
import sys
import time
import pickle

def read_data(f):
    order = 1
    data = {}
    data = collections.defaultdict(dict)
    repititions = 0
    for line in f:
        print line
        words = line.split()
        if words[0] == 'order':
            order = int(words[1])
        elif words[0] == 'repititions':
            repititions = int(words[1])
        else:
            data[order][words[0]] = float(words[1])/float(repititions)

    print data
    return data


def save_data(data):
    with open("performance-data-" + str(time.time()), 'w') as f:
        pickle.dump(data, f)


def main():
    data = None
    print sys.argv[1]
    with open(sys.argv[1], "r") as f:
        data = read_data(f)
        save_data(data)

if __name__ == '__main__':
    main()
