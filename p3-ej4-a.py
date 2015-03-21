#!/usr/bin/env python
import sys
import string
import math

if len(sys.argv) > 2:
    print "Too many arguments"
    sys.exit()
elif len(sys.argv) == 2:
    n =  int(sys.argv[1])
    if n < 2:
        print "n must be greater than 2"
        sys.exit()
    if math.log(n,2) not in [1, 2, 3, 4]:
        print "n must be power of 2 less than 32"
        sys.exit()
else:
    print "Too few arguments"
    sys.exit()

# helper functions
def solveAux(n, p):
    days = []
    if n == 2:
         days.append([p[0], p[1]])
    else:
        # divide
        p1 = p[:n/2]
        p2 = p[n/2:]
        games1 = solveAux(n/2, p1)
        games2 = solveAux(n/2, p2)
        # conquer
        # first merge games1 and games2
        for i in xrange(n/2 - 1):
            days.append([])
            days[i].append(games1[i])
            days[i].append(games2[i])
        # second create the following n/2 days
        for i in xrange(n/2):
            days.append([])

        for i in xrange(n/2):
            for j in xrange(n/2):
                days[n/2 + i - 1].append([p1[j], p2[(j+i) % (n/2)]])
    return days

def solve():
    return solveAux(n, participants)

# initialize
participants = []
for i in xrange(n):
    participants.append(string.lowercase[i])

days = solve()
for i in xrange(n-1):
    print "Day ", i+1,": ",days[i]
