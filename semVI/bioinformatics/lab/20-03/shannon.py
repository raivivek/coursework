#! /usr/bin/env python

from math import log
from sys import stdin

p = lambda p, N: p*1.0/N

def shannon_index(values):
    """ Calculates the Shannon-Wiener diversity index.

    Takes a list of values where the first value is the total number
    of species and the remaining values are distribution of the
    different taxa in sample."""

    N = values[0]
    return sum([p(i, N)*log(p(i, N)) for i in values[1:]])

def simpson_index(values):
    N = values[0]
    return sum([p(i, N)**2 for i in values[1:]])

if __name__ == '__main__':
    values = map(int, stdin.read().split())
    print shannon_index(values)
    print simpson_index(values)
