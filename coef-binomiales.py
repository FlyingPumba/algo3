#!/usr/bin/env python
import sys
import os
import time

if len(sys.argv) > 3:
    print "Too many arguments"
    sys.exit()
elif len(sys.argv) == 3:
    n =  int(sys.argv[1])
    k =  int(sys.argv[2])
    if k > n:
        print "k must be less or equal than n"
        sys.exit()
else:
    print "Too few arguments"
    sys.exit()

# helper functions
def solve():
    m = 1
    for i in xrange(n):
        for j in xrange(m-1):
            matrix[m-j-1] = matrix[m-j-2] + matrix[m-j-1]
        if m < (k+1):
            m = m + 1
    return matrix[k]

# initialize
matrix = [1]*(k+1)
print solve()
